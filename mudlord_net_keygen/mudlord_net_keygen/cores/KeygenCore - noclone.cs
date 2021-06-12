using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.Text;
using Microsoft.VisualBasic;
using Microsoft.VisualBasic.CompilerServices;

namespace keygen
{
    static class KeygenCore
    {
        public enum enumRegType
        {
            rtNotReg,
            rtNetwork,
            rtHome
        }

        public static string Encrypt(string cleanString)
        {
            byte[] bytes = new UnicodeEncoding().GetBytes(cleanString);
            return BitConverter.ToString(((HashAlgorithm)CryptoConfig.CreateFromName("MD5")).ComputeHash(bytes));
        }

        public static string GetRegCode(string PlainText)
        {
            if (PlainText.Length > 8)
            {
                PlainText = PlainText.Substring(0, 8);
            }
            enumRegType NEdition = enumRegType.rtNetwork;
            string[] strArray = Encrypt(Conversions.ToString(Operators.ConcatenateObject("NoClone2007" + PlainText.ToUpper() + "n190854", Interaction.IIf(NEdition == enumRegType.rtHome, "Home", "Enterprise")))).Split(new char[] { '-' });
            string str2 = "";
            {
                int num4 = 8;
                do
                {
                    string str6 = strArray[num4];
                    int num5 = Convert.ToInt32(str6, 0x10) % 0x24;
                    if (num5 > 0x19)
                    {
                        str2 = str2 + Conversions.ToString((int)(num5 - 0x1a));
                    }
                    else
                    {
                        str2 = str2 + Conversions.ToString(Strings.Chr(num5 + 0x41));
                    }
                    num4++;
                }
                while (num4 <= 15);
            }
            return str2.Replace("S", "5").Replace("O", "0").Replace("I", "1");
        }
    }
}
