using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Server_Interface
{
    public class Protocol
    {

        char seperatorChar = ';';
        void SplitString()
        {

        }

        string MakeString(int code, List<string> value, char startChar, char endChar)
        {
            string newString;
            newString = startChar.ToString();
            newString += code;

            foreach (string mess in value)
            {
                newString += seperatorChar;
                newString += mess;
            }
            newString += endChar;
            return newString;
        }

        List<string> SplitString(string text, char splitChar, char startChar, char endChar)
        {
            if ((text[0] == startChar) && (text[text.Length - 1] == endChar))
            {
                text = text.Substring(1, text.Length - 2);
                List<string> returnvalue = new List<string>();
                returnvalue.AddRange(text.Split(splitChar));
                return returnvalue;
            }
            List<string> fu = new List<string>();
            return fu;
        }

    }
}
