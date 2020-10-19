using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace FilePack
{
	class CPackageManager
	{
		byte m_byte = 1;
		int m_int = 2;
		long m_long = 3;
		string m_str = "kakikukekosasisuseso";
		uint m_uint = 128;


		public void TestWrite(string _path){
			using(FileStream file = new FileStream(_path,FileMode.Create)){
				using(BinaryWriter writer = new BinaryWriter(file)){
					writer.Write(m_byte);
					writer.Write(m_int);
					writer.Write(m_long);
					writer.Write(m_str.ToCharArray());
					writer.Write('\0');
					writer.Write(m_uint);
				}

			}
		}

	
	}

	class CReader{
		byte m_byte;
		int m_int;
		long m_long;
		string m_str;
		uint m_uint;

		public void TestReader(string _path){
			using(FileStream file = new FileStream(_path,FileMode.Open)){
				using(BinaryReader reader = new BinaryReader(file)){
					m_byte = reader.ReadByte();
					m_int = reader.ReadInt32();
					m_long = reader.ReadInt64();
					char temp = reader.ReadChar();
					while(temp != '\0'){
						m_str += temp;
						temp = reader.ReadChar();
					}
					
					m_uint = reader.ReadUInt32();
				}
			}
		}

		public void Show(){
			Console.WriteLine("byte : " + m_byte);
			Console.WriteLine("int  : " + m_int);
			Console.WriteLine("long : " + m_long);
			Console.WriteLine("str  : " + m_str);
			Console.WriteLine("uint : " + m_uint);

		}
	}
}
