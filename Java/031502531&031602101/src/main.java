
import java.io.*;
import java.util.regex.Pattern;

public class main {
	private static int ko=0;
	private static BufferedReader br;
	private static boolean isNumeric(String str){
		 Pattern pattern = Pattern.compile("^[0-9]+?$"); 
		return pattern.matcher(str).matches();
	}
	public static void main(String[] args) {
		int w=0;
		int m=1;
		int n=10;
		St begin;	
		File filename = new File("input.txt");;
		File writename = new File("result.txt");;
			for (int i=0; i<args.length; i=i+2) {
				if (args[i].equals("-i")) filename = new File(args[i+1]);
				if (args[i].equals("-o")) writename = new File(args[i+1]);
				if (args[i].equals("-w")) w= Integer.valueOf(args[i+1]);
				if (args[i].equals("-m")) m= Integer.valueOf(args[i+1]);
				if (args[i].equals("-n")) n= Integer.valueOf(args[i+1]);
			}
		ChinaNO1 begining = new ChinaNO1(w,m,n);
		  try { // 防止文件建立或读取失败，用catch捕捉错误并打印，也可以throw  
			  	String pathname = null;
			    // filename = new File(args[0]);  
			 // 	 filename = new File("src/input.txt"); 
	            InputStreamReader reader = new InputStreamReader(  
	                    new FileInputStream(filename)); // 建立一个输入流对象reader  
	            br = new BufferedReader(reader);
	            String line = "";  
	            for (line=br.readLine();line!=null; line=br.readLine()){
	            	 begining.setS(line);
	            //	 begin.getS(begining.getS());
	            	 if (line.length()>0) ko++;
	            }
	            begin=begining.getSt();
	            /* 写入Txt文件 */  
	       //     writename = new File("result.txt"); // 相对路径，如果没有则要建立一个新的output。txt文件  
	            writename.createNewFile(); // 创建新文件  
	            BufferedWriter out = new BufferedWriter(new FileWriter(writename));  
	            out.write("characters: "+String.valueOf(filename.length()-begining.getKazu())+"\r\n");
	            out.write(begin.outws()+"\r\n");
	            out.write(begin.outko()+"\r\n");
	            out.write(begin.outWordN());
	            out.flush(); // 把缓存区内容压入文件  
	            out.close(); // 最后记得关闭文件  
	  
	        } catch (Exception e) {  
	            e.printStackTrace();  
	        }  
	}
}