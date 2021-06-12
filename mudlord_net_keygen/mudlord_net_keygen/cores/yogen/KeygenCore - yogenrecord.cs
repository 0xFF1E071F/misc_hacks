using System;
using System.Collections.Generic;
using System.Collections;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using Microsoft.VisualBasic;
using Microsoft.VisualBasic.CompilerServices;

namespace keygen
{
    class YProfile
    {
        public Hashtable profile;
        public Hashtable profile0;
        public string MyAppDataPath;
        public string dbName;
        public string profilename;
        private byte[] b1;
        private byte[] b2;
        public object readPipe;
        public object writePipe;

        public YProfile()
        {
            this.readPipe = null;
            this.writePipe = null;
            this.MyAppDataPath = null;
            this.b1 = null;
            this.b2 = null;
            this.profile0 = new Hashtable();
            this.profile = Hashtable.Synchronized(this.profile0);
            this.MyAppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
            this.MyAppDataPath = Path.Combine(this.MyAppDataPath, "YoGen");
            this.dbName = "YoGenVocalRemoverWin";
            YPathNotExitsThenCreateIt(this.MyAppDataPath);
            this.profilename = Path.Combine(this.MyAppDataPath, this.dbName) + ".profile";
        }

        public static bool YPathNotExitsThenCreateIt(string path)
        {
            string pathRoot = Path.GetPathRoot(path);
            string[] strArray = path.Remove(0, pathRoot.Length).Split(new char[] { Path.DirectorySeparatorChar });
            string str3 = pathRoot;
            for (int i = 0; i < strArray.Length; i++)
            {
                str3 = Path.Combine(str3, strArray[i]);
                if (!Directory.Exists(str3))
                {
                    Directory.CreateDirectory(str3);
                }
            }
            return true;
        }

        public void WriteBool(string key, bool value)
        {
            key = string.Format("{0}_{1}", Environment.UserName, key);
            this.WriteBoolGlobal(key, value);
        }

        public void WriteBoolGlobal(string key, bool value)
        {
            lock (profile.SyncRoot)
            {
                if (profile.ContainsKey(key))
                {
                    profile.Remove(key);
                    profile.Add(key, value);
                }
                else
                {
                    profile.Add(key, value);
                }
            }
        }

        public void WriteDouble(string key, double value)
        {
            key = string.Format("{0}_{1}", Environment.UserName, key);
            this.WriteDoubleGlobal(key, value);
        }

        public void WriteDoubleGlobal(string key, double value)
        {
            lock (this.profile.SyncRoot)
            {
                if (this.profile.ContainsKey(key))
                {
                    this.profile.Remove(key);
                    this.profile.Add(key, value);
                }
                else
                {
                    this.profile.Add(key, value);
                }
            }
        }

        public void WriteInt(string key, int value)
        {
            key = string.Format("{0}_{1}", Environment.UserName, key);
            this.WriteIntGlobal(key, value);
        }

        public void WriteIntGlobal(string key, int value)
        {
            lock (this.profile.SyncRoot)
            {
                if (this.profile.ContainsKey(key))
                {
                    this.profile.Remove(key);
                    this.profile.Add(key, value);
                }
                else
                {
                    this.profile.Add(key, value);
                }
            }
        }

        public void WriteObjectGlobal(object key, object value)
        {
            lock (this.profile.SyncRoot)
            {
                if (this.profile.ContainsKey(key))
                {
                    this.profile.Remove(key);
                    this.profile.Add(key, value);
                }
                else
                {
                    this.profile.Add(key, value);
                }
            }
        }

        public void WriteString(string key, string value)
        {
            key = string.Format("{0}_{1}", Environment.UserName, key);
            this.WriteStringGlobal(key, value);
        }

        public void WriteStringGlobal(string key, string value)
        {
            lock (this.profile.SyncRoot)
            {
                if (this.profile.ContainsKey(key))
                {
                    this.profile.Remove(key);
                    this.profile.Add(key, value);
                }
                else
                {
                    this.profile.Add(key, value);
                }
            }
        }

        public void StoreProfile()
        {
            IFormatter formatter = new BinaryFormatter();
            MemoryStream serializationStream = new MemoryStream();
            formatter.Serialize(serializationStream, this.profile);
            byte[] buffer = serializationStream.GetBuffer();
            serializationStream.Close();
            DESCryptoServiceProvider provider = new DESCryptoServiceProvider();
            ICryptoTransform transform = null;
            try
            {
                transform = provider.CreateEncryptor(this.b1, this.b2);
            }
            catch
            {
                this.b1 = provider.Key;
                this.b2 = provider.IV;
                transform = provider.CreateEncryptor(this.b1, this.b2);
            }
           
            string path = Path.Combine(this.MyAppDataPath, this.dbName) + "_temp";
            Stream stream = null;
            try
            {
                stream = new FileStream(path, FileMode.Create, FileAccess.Write, FileShare.None);
            }
            catch (DirectoryNotFoundException exception)
            {
                MessageBox.Show(exception.Message);
                return;
            }
            stream.WriteByte((byte)this.b1.Length);
            stream.WriteByte((byte)this.b2.Length);
            stream.Write(this.b1, 0, this.b1.Length);
            stream.Write(this.b2, 0, this.b2.Length);
            CryptoStream stream3 = new CryptoStream(stream, transform, CryptoStreamMode.Write);
            stream3.Write(buffer, 0, buffer.Length);
            stream3.Close();
            stream = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.None);
            byte[] buffer2 = new byte[stream.Length];
            stream.Read(buffer2, 0, buffer2.Length);
            stream.Close();
            File.Delete(path);
            Stream stream4 = new FileStream(this.profilename, FileMode.Create, FileAccess.Write, FileShare.None);
            stream4.Write(buffer2, 0, buffer2.Length);
            stream4.Close();
        }

    }
}

