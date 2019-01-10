using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server_Interface
{
    public static class Protocol
    {
        public static char startCharToServer = '$';
        public static char seperatorChar = ';';
        public static char endCharToServer = '#';

        public static string MakeString(CP_Code code, List<string> value)
        {
            string newString;
            newString = startCharToServer.ToString();
            newString += (int)code;

            foreach (string mess in value)
            {
                newString += seperatorChar;
                newString += mess;
            }
            newString += endCharToServer;
            return newString;
        }

        public static List<string> SplitString(string text)
        {
            if ((text[0] == endCharToServer) && (text[text.Length - 1] == startCharToServer))
            {
                text = text.Substring(1, text.Length - 2);
                List<string> returnvalue = new List<string>();
                returnvalue.AddRange(text.Split(seperatorChar));
                return returnvalue;
            }
            List<string> fu = new List<string>();
            return fu;
        }
    }
}
