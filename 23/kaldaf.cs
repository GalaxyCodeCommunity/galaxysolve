// CONSOLE APP

using System;

namespace Ceasar
{
    class Program
    {
        static void Main()
        {
            while (true)
            {
                Console.WriteLine("Slovo");
                string v = Console.ReadLine();

                if (string.IsNullOrEmpty(v))
                {
                    Console.WriteLine("Něco je asi špatně \n");
                    continue;
                }

                Console.WriteLine("Posun");
                string m = Console.ReadLine();


                if (!int.TryParse(m, out int va))
                {
                    Console.WriteLine("Něco je asi špatně \n");
                    continue;
                }

                if (System.Text.RegularExpressions.Regex.IsMatch(m, "[^0-9 , -]"))
                {
                    Console.WriteLine("Něco je asi špatně \n");
                    continue;
                }

                Console.WriteLine("\n Super secret: " +doCrypt(v, Int32.Parse(m)) + "\n");
            }
        }
        private static string doCrypt(string value, int move)
        {
            char[] memory = value.ToCharArray();
            for (int i = 0; i < memory.Length; i++)
            {
                char letter = memory[i];
                letter = (char)(letter + move);

                if (letter > 'z')
                {
                    letter = (char)(letter - 26);
                }
                else if (letter < 'a')
                {
                    letter = (char)(letter + 26);
                }
                memory[i] = letter;
            }
            return new string(memory);
        }

    }
}
