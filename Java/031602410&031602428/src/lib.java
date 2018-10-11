import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.CharArrayWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.Map.Entry;

public class lib {
	
	static List<String> titleLists = new ArrayList<String>();
	static List<String> abstractLists = new ArrayList<String>();
    static Map<String, Integer> wordsCount = new TreeMap<String,Integer>();  
	
	public static void SortMap(Map<String,Integer> oldmap,int wordline,int wordcount,int characterscount,int flagN) throws IOException{  
        
        ArrayList<Map.Entry<String,Integer>> list = new ArrayList<Map.Entry<String,Integer>>(oldmap.entrySet());  
          
        Collections.sort(list,new Comparator<Map.Entry<String,Integer>>(){  
            @Override  
            public int compare(Entry<String, Integer> o1, Entry<String, Integer> o2) {  
                return o2.getValue() - o1.getValue();  //降序  
            }  
        });  
        File file = new File("result.txt");
        BufferedWriter bi = new BufferedWriter(new FileWriter(file));
        bi.write("characters: "+characterscount+"\r\n");
        bi.write("words: "+wordcount+"\r\n");
        bi.write("lines: "+wordline+"\r\n");
        int flag = 0;
        for(int i = 0; i<list.size(); i++){  
        	if(flag>=flagN) break;
        	if(list.get(i).getKey().length()>=4)
        		bi.write("<"+list.get(i).getKey()+">"+ ": " +list.get(i).getValue()+"\r\n"); 
        	flag++;
        }
        bi.close();
    }
	
	public static String Read(String pathname) throws Exception {
//		Scanner scanner=new Scanner(System.in);
//    	String pathname=scanner.nextLine();


    	Reader myReader = new FileReader(pathname);
    	Reader myBufferedReader = new BufferedReader(myReader);
    	

    	//先对文本处理
    	
    	CharArrayWriter  tempStream = new CharArrayWriter();
    	int i = -1;
    	do {
    		if(i!=-1)
    			tempStream.write(i);
    		i = myBufferedReader.read();
    		if(i >= 65 && i <= 90){
    				i += 32;
    		}
    	}while(i != -1);
    	myBufferedReader.close();
    	Writer myWriter = new FileWriter(pathname);
    	tempStream.writeTo(myWriter);
    	tempStream.flush();
    	tempStream.close();
    	myWriter.close();
		return pathname;
	}

	public static void FindWordArray(List<String> tempLists, int len, String wordsLine) {
		
		int tempi = 0;
		int cnti = 0;
		int cntt = 0;
		String temp = "";
		String[] words = new String[len];
		String[] separators = new String[len];
		for(int i = 0; i < wordsLine.length(); i++) {
			//The four words in front of a new word
			if (tempi < 4 && Character.isLetter(wordsLine.charAt(i)))
			{
				tempi ++;
//				System.out.println("<4 " + i + " " + wordsLine.charAt(i));
				temp = temp + wordsLine.charAt(i);
				
				//A new word appear.
				if (i == wordsLine.length() - 1) {
					words[cnti%len] = temp;
					cnti ++;
					cntt ++;
//					System.out.println("word " + temp);
					
					//A new wordarray appear.
					if(cntt == len) {
						String wordArray = "";
						for(int j = 0; j < len; j++) {
							wordArray = wordArray + words[(cnti + j)%len];
							if(j != len-1)	wordArray = wordArray + separators[(cnti + j)%len];
						}
						tempLists.add(wordArray);
//						System.out.println("wordArray " + wordArray);
						cntt --;
					}
				}
			}
			else if (tempi >= 4) {
				tempi ++;
				if(Character.isLetter(wordsLine.charAt(i)) || Character.isDigit(wordsLine.charAt(i))) {
//					System.out.println("1 >=4 " + i + " " + wordsLine.charAt(i));
					temp = temp + wordsLine.charAt(i);
					
					//A new word appear.
					if (i == wordsLine.length() - 1) {
						words[cnti%len] = temp;
						cnti ++;
    					cntt ++;
//						System.out.println("word " + temp);
    					
						//A new wordArray appear.
						if(cntt == len) {
							String wordArray = "";
							for(int j = 0; j < len; j++) {
								wordArray = wordArray + words[(cnti + j)%len];
								if(j != len-1)	wordArray = wordArray + separators[(cnti + j)%len];
							}
							
//							add wordArray to list
							tempLists.add(wordArray);
//							System.out.println("wordArray " + wordArray);
							cntt --;
						}
					}
				}
				else {
//					System.out.println("2 >=4 " + i + " " + wordsLine.charAt(i));
					
					//A new word appear.And a separator appear.
					words[cnti%len] = temp;
					cnti ++;
					cntt ++;
//					System.out.println("word 123 " + temp);
					if(cntt == len) {
						String wordArray = "";
						for(int j = 0; j < len; j++) {
							wordArray = wordArray + words[(cnti + j)%len];
							if(j != len-1)	wordArray = wordArray + separators[(cnti + j)%len];
						}
//						add wordArray to list
						tempLists.add(wordArray);
//						System.out.println("wordArray " + wordArray);
						cntt --;
					}
					if (i + 4 >= wordsLine.length())
						break;
					tempi = 0;
					temp = "";
					
					//draw a separator
					String tempSeparator = "" + wordsLine.charAt(i);
//					System.out.println("Separator" + tempSeparator + "123");
					for(int j = 1; j < wordsLine.length() - i; j++) {
						if( Character.isDigit(wordsLine.charAt(i+j)) || Character.isLetter(wordsLine.charAt(i+j)) ) {
//							System.out.println("123");
							temp = "";
							separators[(cnti-1)%len] = tempSeparator;
							break;
						}
						else	tempSeparator = tempSeparator + wordsLine.charAt(i+j);
					}
				}
			}
			
			//A invalid word appear
			else {
//				System.out.println("invalid " + i + "" + wordsLine.charAt(i));
				if (i + 4 >= (int)wordsLine.length()) 
					break;
				tempi = 0;
				temp = "";
				cnti = 0;
				cntt = 0;
			}
		}
	}

	public static void WordCount(List<String> tempLists,int weight) {
		for (String li : tempLists) {  
            if(wordsCount.get(li) != null){ 
            	wordsCount.put(li,wordsCount.get(li) + weight);  
            }else{  
            	wordsCount.put(li,weight);  
            }  
  
        } 
	}
}
