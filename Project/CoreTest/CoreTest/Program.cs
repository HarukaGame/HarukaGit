using System;
using System.IO;

namespace CoreTest
{
	class Program
	{
		static void Main(string[] args)
		{
			if(args.Length != 3){
				Console.WriteLine("引数の数が不正です");
				return;
			}

			string inputFile = args[0];
			string outputFile = args[1];
			string ignore = args[2];

			if(Directory.Exists(inputFile) == false){
				Console.WriteLine(inputFile + "は存在しません");
			}else{
				Console.WriteLine(inputFile + "は存在します");
			}


			if (Directory.Exists(outputFile) == false)
			{
				Console.WriteLine(outputFile + "は存在しません。生成します");
				Directory.CreateDirectory(outputFile);
			}else{
				Console.WriteLine(outputFile + "は存在します");
			}
			string writeFile = Path.Combine(outputFile, "file.txt");
			//File.Create(writeFile);
			using (StreamWriter write = new StreamWriter(writeFile)){
				string[] inputFiles = Directory.GetFiles(inputFile, "*", SearchOption.TopDirectoryOnly);
				foreach(string input in inputFiles){
					string[] inputLines = File.ReadAllLines(input);
					foreach(string line in inputLines){
						write.WriteLine(line);
					}
					write.WriteLine('\0');
				}

				if (File.Exists(ignore) == false){
					Console.WriteLine(ignore + "は存在しません");
				}else{
					string[] ignoreLines = File.ReadAllLines(ignore);
					Console.WriteLine("無視リスト");
					Console.WriteLine("---------------------------------------");
					foreach(string line in ignoreLines){
						Console.WriteLine(line);
					}
					Console.WriteLine("---------------------------------------");

				}

			}


			string[] result = File.ReadAllLines(writeFile);
			foreach(string line in result){
				Console.WriteLine(line);
			}
		}
	}
}
