using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace keygen
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            cbProduct.Items.Add("YoGen Recorder");
            cbProduct.Items.Add("YoGen Vocal Remover");
            cbProduct.Items.Add("YoGen Vocoder");
            cbProduct.Items.Add("YoGen Converter");
            cbProduct.SelectedIndex = 0;

        }

        public int RandomNumber(int min, int max)
        {
        Random random = new Random();
        return random.Next(min, max);
        }

        private string RandomString(int size, bool lowerCase)
        {
            StringBuilder builder = new StringBuilder();
            Random random = new Random();
            char ch;
            for (int i = 0; i < size; i++)
            {
                ch = Convert.ToChar(Convert.ToInt32(Math.Floor(26 * random.NextDouble() + 65)));
                builder.Append(ch);
            }
            if (lowerCase)
                return builder.ToString().ToLower();
            return builder.ToString();
        }

        public void GenSerial()
        {
            YProfile profile = new YProfile();
            string sName = RandomString(10,false);
            string sKey;
            sName = txtName.Text.Trim();
            string sEmail = sName + "@goatse.cx";
            int key1, key2, key3, key4;
            
            if (sName.Length == 0)
            {
                MessageBox.Show("Enter a name!!!");
            }
            else
            {
            switch(cbProduct.SelectedIndex)
            {
                case 0:
                    profile.YInit("YoGenRecorderWin");
                    break;
                case 1:
                    profile.YInit("YoGenVocalRemoverWin");
                    break;
                case 2:
                    profile.YInit("YoGenVocoderWin");
                    break;
                case 3:
                    profile.YInit("YoGenConverterWin");
                    break;
            }
            key1 = RandomNumber(1000, 9000);
            key2 = RandomNumber(1000, 9000);
            key3 = RandomNumber(1000, 9000);
            key4 = RandomNumber(1000, 9000);
            sKey = string.Format("{0}-{1}-{2}-{3}", new object[] { key1, 
            key2,key3, key4 });
            profile.WriteStringGlobal("sEmail", sEmail);
            profile.WriteStringGlobal("sKey", sKey);
            profile.WriteStringGlobal("sName", sName);
            profile.WriteBoolGlobal("bLicense", true);
            profile.StoreProfile();
            MessageBox.Show("Keyfile generated.\nEnjoy this fine UNiQUE release!");
            }
        }

        private void Generate_Click(object sender, EventArgs e)
        {
            GenSerial();
        }
    }
}
