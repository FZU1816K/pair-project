import java.io.*; //File
import java.util.*;//Scanner Map
import lib.*;
public class Main {
	public static void main(String[] args) throws Exception {
		int mn = 1, nn = 10, wn = 0;
		String fi = " ", fo = " ";
		Map<String, Integer> words = new TreeMap<String, Integer>();
		for(int i=0; i<args.length; i+=2) {
			if(args[i].equals("-i"))
				fi = args[i+1];
			if(args[i].equals("-m"))
				mn = Integer.parseInt((args[i+1]));
			if(args[i].equals("-n"))
				nn = Integer.parseInt((args[i+1]));
			if(args[i].equals("-w"))
				wn = Integer.parseInt((args[i+1]));
			if(args[i].equals("-o"))
				fo = args[i+1];
		}
		if (fi.equals(" ")) {
			System.out.println("Please input \"-i any txt\"");
			System.exit(0);
		}
		if(fo.equals(" ")) {
			System.out.println("Please input \"-o any txt\"");
			System.exit(0);
		}
		PrintStream result = new PrintStream(fo);
		File f = new File(fi);
		if (!f .exists()) {
			System.out.println("The txt does not exist.");
			System.exit(0);
		}	
		try(Scanner input = new Scanner(f)){
			int countOfCharacters = 0;
			int countOfLine = 0;
			int countOfWords = 0;
			while (input.hasNext()) {
				String line = input.nextLine();
				countOfCharacters += line.length();//计算当前行的字符个数
				String[] cc = line.split("[^\\w\\d]+");
				if(!cc[0].matches("[0-9]")) {
				if((cc[0].equals("Title"))||(cc[0].equals("Abstract")))
				countOfCharacters -= (cc[0].length()+2);
				countOfLine ++;
				countOfWords += CountWords.countWords(line, words,mn,wn); //CountWords内的static方法countWords
				}
			}
			System.setOut(result);
			System.out.println("characters: " + countOfCharacters);
			System.out.println("words: " +countOfWords);
			System.out.println("lines: " +countOfLine);
			CountMaxOfWords.Sort(words,nn);//CountMaxOfWords内的static方法Sort
		}
		catch(Exception ex) {
			ex.printStackTrace();
		}
	}
}