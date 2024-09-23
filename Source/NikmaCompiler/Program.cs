using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using System.Threading;

namespace NikmaASM
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                bool debug = false;
                bool x64 = false;
                string path = args[0];
                for (int i = 1; i < args.Length; i++)
                {
                    switch (args[i])
                    {
                        case "-d":
                        case "--debug":
                            debug = true;
                            break;
                        case "-h":
                        case "--help":
                            Help();
                            break;
                        case "-x64":
                            x64 = true;
                            break;
                        default:
                            Console.WriteLine($"Invalid argument {args[i]}");
                            Help();
                            return;
                    }
                }
                if (File.Exists(path))
                {
                    NikmaASM nikmaASM = new NikmaASM();
                    nikmaASM.Create(File.ReadAllLines(path), debug);
                    File.WriteAllLines(@"NikmaVM\Instructions.h", nikmaASM.instruction);
                    nikmaASM.Compile(path, x64);
                }
                else
                {
                    Console.WriteLine("The file was not found!");
                }
            }
            else
            {
                Help();
            }
        }
        static void Help()
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Use: NikmaCompiler.exe <file.nikasm> [option] ");
            Console.WriteLine("Options:");
            Console.ForegroundColor = ConsoleColor.White;
            Console.WriteLine(String.Format("  {0,5}    {1,10}", "-h, --help", "Get help"));
            Console.WriteLine(String.Format("  {0,5}    {1,10}", "-d, --debug", "Enable VM debug"));
            Console.WriteLine(String.Format("  {0,5}    {1,10}", "-x64", "Compile x64 (default x32)"));
        }
    }
    public class NikmaASM
    {
        public List<string> instruction = new List<string>();

        string[] registers = { "ra", "rb", "rc", "rd", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "sp", "ip" };
        string[] commands = { "mov", "add", "sub", "div", "mul", "mod", "and", "xor", "or", "pop", "push", "cmp", "jz", "jnz", "jmp", "stdout", "stdin", "exit", "call", "import", "clr" };
        public void Create(string[] asmCode, bool debug)
        {
            if (debug)
            {
                instruction.Add("#define DEBUG 1");
            }
            instruction.Add("#ifndef INSTRUCTIONS_H");
            instruction.Add("#define INSTRUCTIONS_H");
            instruction.Add($"Instruction instructions[{asmCode.Length}] = {{");

            foreach (string line in asmCode)
            {
                string[] components = Regex.Split(line, @" (?=(?:[^""]*""[^""]*"")*[^""]*$)");
                string command = components[0];
                if (commands.Contains(command))
                {
                    switch (command)
                    {
                        case "mov":
                        case "add":
                        case "sub":
                        case "div":
                        case "mul":
                        case "mod":
                        case "and":
                        case "xor":
                        case "or":
                            {
                                string arg1 = components[1].Replace(",", "");
                                string arg2 = components[2];
                                if (IsRegister(arg1) && IsRegister(arg2))
                                {
                                    Reg2RegHandle($"OP_{command.ToUpper()}_r", arg1, arg2);
                                }
                                else if (IsRegister(arg1) && int.TryParse(arg2, out int number))
                                {
                                    Num2RegHandle($"OP_{command.ToUpper()}_n", arg1, arg2);
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                        case "pop":
                            {
                                string arg1 = components[1];
                                if (IsRegister(arg1))
                                {
                                    RegHandle("OP_POP_r", arg1);
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                        case "push":
                            {
                                string arg1 = components[1];
                                if (IsRegister(arg1))
                                {
                                    RegHandle($"OP_{command.ToUpper()}_r", arg1);
                                }
                                else if (int.TryParse(arg1, out int number))
                                {
                                    NumHandle($"OP_{command.ToUpper()}_n", arg1);
                                }
                                else if (arg1[0] == '\"' && arg1[arg1.Length - 1] == '\"')
                                {
                                    StrHandle($"OP_{command.ToUpper()}_s", arg1);
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                        case "jz":
                        case "jnz":
                        case "jmp":
                        case "exit":
                            {
                                string arg1 = components[1];
                                if (IsRegister(arg1))
                                {
                                    RegHandle($"OP_{command.ToUpper()}_r", arg1);
                                }
                                else if (int.TryParse(arg1, out int number))
                                {
                                    NumHandle($"OP_{command.ToUpper()}_n", arg1);
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                        case "cmp":
                            {
                                string arg1 = components[1].Replace(",", "");
                                string arg2 = components[2];
                                if (IsRegister(arg1) && IsRegister(arg2))
                                {
                                    Reg2RegHandle($"OP_{command.ToUpper()}_r", arg1, arg2);
                                }
                                else if (IsRegister(arg1) && int.TryParse(arg2, out int number))
                                {
                                    Num2RegHandle($"OP_{command.ToUpper()}_n", arg1, arg2);
                                }
                                else if (arg1[0] == '[' && arg1[arg1.Length - 1] == ']' && arg2[0] == '[' && arg2[arg2.Length - 1] == ']')
                                {
                                    arg1 = arg1.Replace("[", "").Replace("]", "");
                                    arg2 = arg2.Replace("[", "").Replace("]", "");
                                    if (IsRegister(arg1) && IsRegister(arg2))
                                    {
                                        Reg2RegHandle($"OP_{command.ToUpper()}_p", arg1, arg2);
                                    }
                                    else
                                    {
                                        Console.WriteLine("Invalid argument!");
                                        return;
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                        case "stdout":
                            {
                                string arg1 = components[1];
                                if (IsRegister(arg1))
                                {
                                    RegHandle($"OP_{command.ToUpper()}_r", arg1);
                                }
                                else if (arg1[0] == '[' && arg1[arg1.Length - 1] == ']')
                                {
                                    arg1 = arg1.Replace("[", "").Replace("]", "");
                                    if (IsRegister(arg1))
                                    {
                                       RegHandle($"OP_{command.ToUpper()}_p", arg1);
                                    }
                                    else
                                    {
                                        Console.WriteLine("Invalid argument!");
                                        return;
                                    }
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                        case "stdin":
                        case "clr":
                            {
                                Handle($"OP_{command.ToUpper()}");
                                break;
                            }
                        case "call":
                        case "import":
                            {
                                string arg1 = components[1];
                                if (arg1[0] == '[' && arg1[arg1.Length - 1] == ']')
                                {
                                    arg1 = arg1.Replace("[", "").Replace("]", "");
                                    if (IsRegister(arg1))
                                    {
                                        RegHandle($"OP_{command.ToUpper()}_p", arg1);
                                    }
                                    else
                                    {
                                        Console.WriteLine("Invalid argument!");
                                        return;
                                    }
                                }
                                else if (arg1 != String.Empty)
                                {
                                    StrHandle($"OP_{command.ToUpper()}_s", $"\"{arg1}\"");
                                }
                                else
                                {
                                    Console.WriteLine("Invalid argument!");
                                    return;
                                }
                                break;
                            }
                    }
                }
            }
            string lastStr = instruction[instruction.Count - 1].Remove(instruction[instruction.Count - 1].Length-1);
            instruction[instruction.Count - 1] = lastStr;
            instruction.Add("};");
            instruction.Add("#endif INSTRUCTIONS_H");
        }
        private bool IsRegister(string reg)
        {
            for (int i = 0; i < registers.Length; i++)
            {
                if (reg == registers[i])
                {
                    return true;
                }
            }
            return false;
        }
        private void Reg2RegHandle(string opcode, string arg1, string arg2)
        {
            instruction.Add("{");
            instruction.Add($".opcode = {opcode},");
            instruction.Add($".first_operand.reg = {arg1},");
            instruction.Add($".second_operand.reg = {arg2}");
            instruction.Add("},");
        }
        private void Num2RegHandle(string opcode, string arg1, string arg2)
        {
            instruction.Add("{");
            instruction.Add($".opcode = {opcode},");
            instruction.Add($".first_operand.reg = {arg1},");
            instruction.Add($".second_operand.num = {arg2}");
            instruction.Add("},");
        }
        private void StrHandle(string opcode, string arg1)
        {
            instruction.Add("{");
            instruction.Add($".opcode = {opcode},");
            instruction.Add($".first_operand.str = {arg1}");
            instruction.Add("},");
        }
        private void NumHandle(string opcode, string arg1)
        {
            instruction.Add("{");
            instruction.Add($".opcode = {opcode},");
            instruction.Add($".first_operand.num = {arg1}");
            instruction.Add("},");
        }
        private void RegHandle(string opcode, string arg1)
        {
            instruction.Add("{");
            instruction.Add($".opcode = {opcode},");
            instruction.Add($".first_operand.reg = {arg1}");
            instruction.Add("},");
        }
        private void Handle(string opcode)
        {
            instruction.Add("{");
            instruction.Add($".opcode = {opcode}");
            instruction.Add("},");
        }
        public void Compile(string path, bool x64)
        {
            string TccPath = @"tcc\tcc.exe";
            string outputFile = path.Replace(Path.GetFileName(path), Path.GetFileName(path).Replace(".nikasm", ".exe"));
            string arguments;
            if (x64)
            {
                arguments = $@"NikmaVM\*.c -m64 -w -o {outputFile}";
            }
            else
            {
                arguments = $@"NikmaVM\*.c -m32 -w -o {outputFile}";
            }
            Process process = new Process();
            process.StartInfo.FileName = TccPath;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.Arguments = arguments;
            process.StartInfo.RedirectStandardOutput = true;
            process.Start();
            process.StandardOutput.ReadToEnd();
        }
    }
}

