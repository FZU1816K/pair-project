package lib;
import java.util.*;
//统计单词数
public class CountWords {
	public static int countWords(String line, Map<String, Integer> m, int mn, int wn) {
		String mline = line.toLowerCase();
		String[] words = mline.split("[^\\w\\d]+");
		String[] uu = mline.split("[\\w\\d]+");
		int wcount = words.length-1;
		int w = 0, t = 1, k = 0;
		String ww = "";
		if((words[0].equals("title"))&&(wn==1)) {
			t = 10;
		}
		if((words[0].equals("title"))||(words[0].equals("abstract"))) {
			k = 1;
		}
		for(int i=k; i<words.length; i++){
			if(words[i].length() < 4) {
				wcount--;
				w = 0;
				ww = "";
			}
			if(words[i].length() >= 4){
				//System.out.println(words[i]);
				char[] word = words[i].toCharArray();
				int mcount = 0;
				for(int j=0; j<4; j++){
					if((word[j]>='0') && (word[j]<='9')){
						mcount++;
					}
				}
				//System.out.println(mcount);
				if((mcount == 0)){
					if(w == 0) {
						ww += words[i];
					}
					else {
						ww +=uu[i]+words[i];
					}
					w++;
				}
				if(mcount != 0){
					ww = "";
					w = 0;
					wcount--;
				}
			}
			if(w == mn) {
				//System.out.println(ww);
				if(m.containsKey(ww)){
					int v = (Integer)m.get(ww);
					v+=t;
					m.put(ww,v);
				}
				else{
					m.put(ww,t);
				}
				ww = "";
				w = 0;
				i = i-mn+1;
			}
		}
		return wcount;
	}
}