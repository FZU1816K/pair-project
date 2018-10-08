import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import lib.Read;

public class Main {
	public static void main(String[] args) throws Exception {
		
		//split argument of arguments
		String readFile = "";
		String writeFile = "";
		int number = 0, len = 0, weight = 0;
		for (int i = 0; i < args.length; i+=2) {
			switch (args[i]) {
				case "-i":
					readFile = args[i+1];
					break;
				case "-o":
					writeFile = args[i+1];
					break;
				case "-m":		
					len = Integer.parseInt(args[i+1]);
					break;
				case "-n":
					number = Integer.parseInt(args[i+1]);
					break;
				case "-w":
					weight = Integer.parseInt(args[i+1]);
					break;
			}
		}
		
//		System.out.println("-i " + readFile);
//		System.out.println("-o " + writeFile);
//		System.out.println("-m " + len);
//		System.out.println("-n " + number);
//		System.out.println("-w " + weight);
		
		//file 
    	new Read();
		String pathname = Read.Read(readFile);
    	
    	BufferedReader bufferedReader = new BufferedReader(new FileReader(pathname));  
    	
    	//init
    	int characterscount = 0;
        int wordline = 0;
        int wordcount = 0;
    	
    	//处理-w
    	//w = 0;
    	/*
    	 *  Pattern p = Pattern.compile("a*b");
 			Matcher m = p.matcher("aaaaab");
 			boolean b = m.matches();
    	 */
    	List<String> titleLists = new ArrayList<String>();
    	List<String> abstractLists = new ArrayList<String>();
    	String readLine = null;
    	Pattern pattern1 = Pattern.compile("(title): (.*)");
    	Pattern pattern2 = Pattern.compile("(abstract): (.*)");
    	while((readLine = bufferedReader.readLine()) != null)
    	{  
    		Matcher matcher1=pattern1.matcher(readLine);
    		Matcher matcher2=pattern2.matcher(readLine);
        	if(matcher1.find())
        	{  
        		characterscount+=matcher1.group(2).length();
        		wordline++;
        		//System.out.println(matcher1.group(2));
        		String[] wordsArr1 = matcher1.group(2).split("[^a-zA-Z0-9]");  //过滤
        		for (String newword : wordsArr1) {  
        			if(newword.length() != 0){  
                    	if((newword.length()>=4)&&(Character.isLetter(newword.charAt(0))&&Character.isLetter(newword.charAt(1))&&Character.isLetter(newword.charAt(2))&&Character.isLetter(newword.charAt(3)))) 
                     	{
                     		wordcount++;
                     		titleLists.add(newword);  
                     	}
                     }
        		}  
        	 }
        	 if(matcher2.find())
        	 {
        		 characterscount+=matcher2.group(2).length();
        		 wordline++;
        		 //System.out.println(matcher1.group(2));
        		 String[] wordsArr2 = matcher2.group(2).split("[^a-zA-Z0-9]");  //过滤
        		 for (String newword : wordsArr2) {  
                 	if(newword.length() != 0){
                    	if((newword.length()>=4)&&(Character.isLetter(newword.charAt(0))&&Character.isLetter(newword.charAt(1))&&Character.isLetter(newword.charAt(2))&&Character.isLetter(newword.charAt(3)))) 
                    	{
                    		wordcount++;
                    		abstractLists.add(newword);  
                    	}
                    }  
                }  
        	 }
    	}
	}
}
