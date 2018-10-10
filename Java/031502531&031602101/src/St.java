import java.util.*;

public class St {
	private static String s;
	private static String kon="";
	private Queue<Integer> Qi= new LinkedList<Integer>();
	private static int sl=0;
	private static int ws=0;
	private static int ko=0;
	private static int w=0;
	private static int m=0;
	private static int n=0;
	private HashMap<String, Integer > hashMap=new HashMap<String,Integer>();
	private Set<String> wordSet=hashMap.keySet();
	public String outsl(){	return 	"characters: "+String.valueOf(sl);	}
	public String outws(){	return "words: "+String.valueOf(ws);	}
	public String outko(){	return	"lines: "+String.valueOf(ko);	}
	public String outWordN(){
		String kk="";
		List<String> list=new ArrayList<String>(wordSet);
		List<Integer> list2=new ArrayList<Integer>();
		Collections.sort(list);
		for(int i=0;i<list.size();i++) list2.add(hashMap.get(list.get(i)));	
		Collections.sort(list2);
		for (int j=1; j<=n; j++)
			for (int i=0;i<list.size();i++){
				if (hashMap.get(list.get(i))==list2.get(list2.size()-j)){
					kk=kk+"<"+list.get(i)+">: "+hashMap.get(list.get(i))+"\r\n";
					list.remove(i);
					break;
				}
			}
		return kk;
	}
	public boolean syadann(int c){
		if (c>=48 && c<=57) return false;
		if (c>=65 && c<=90) return false;
		if (c>=97 && c<=122) return false;
		return true;
	}
	public boolean eigo(int c){
		if (c>=65 && c<=90) return true;
		if (c>=97 && c<=122) return true;
		return false;
	}
	public void getS(String s,int w){
		if (s!=null){
		    St.s=s.toLowerCase();	
		    St.w=w;
		    st3("", 0,0);
		    st1();
			st2();
		}
	}
	private void wordPush(String sk) {
		if(wordSet.contains(sk))
		{
			Integer number=hashMap.get(sk);
			number=number+w;
			hashMap.put(sk, number);
		}
		else 
		{
			hashMap.put(sk, w);
		}
	}
	public St(int m,int n){
		this.m=m;
		this.n=n;
	}
	public void st1(){	//计算有效行数 非空行++
		for(int i=0;i<s.length();i++){
			char ch = s.charAt(i);
			int j=(int)ch;
			if (j!=32 && j!=9) {
				ko++;
				return;
			}
		}
	}
	public void st2(){	//计算单词数量
		int k=0;
		boolean ikeru=true;
		String th="";
		for(int i=0;i<s.length();i++){
			char ch = s.charAt(i);
			int j=(int)ch;
			if (!syadann(j)){
				th=th+ch;
			}
			if (ikeru && eigo(j)){
				k++;
			}else if (ikeru && !eigo(j)) ikeru=false;
			if (syadann(j) || i==s.length()-1) {
				if (k>=4) {
					ws++;
				//	wordPush(th);
					int f=i;
					while (f<s.length() && syadann((int)s.charAt(f))) th=th+s.charAt(f++);
					st3(th, m,f-i);
				}
				else st3("", 0,0);
				ikeru=true;
				k=0;
				th="";
			}
		}	
	}
	public void st3(String s,int k,int tail){
		if (k==0) {
			kon="";
			while (!Qi.isEmpty()) Qi.remove();
			return;
		}
		Qi.offer(s.length());
		if (Qi.size()>k) kon=kon.substring(Qi.remove());
		kon=kon+s;
		if (Qi.size()==k) wordPush(kon.substring(0, kon.length()-tail));
	}
}
