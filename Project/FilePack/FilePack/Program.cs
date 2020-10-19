using System;
using System.IO;
using System.Runtime.InteropServices;

namespace FilePack
{
	class Program
	{
		static void Main(string[] args)
		{
			string path = @"C:\Users\user\Desktop\testfolder\createfile.txt";

			if(File.Exists(path) == false){
				using (File.Create(path)){}
			}
			using (FileStream file = new FileStream(path,FileMode.Create)){

			}

			CPackageManager manager = new CPackageManager();
			manager.TestWrite(path);


			CReader reader = new CReader();
			reader.TestReader(path);
			reader.Show();
		}

	}
}
