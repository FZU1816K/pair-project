
public class mainbody {

	public static void main(String[] args) {	//.class目录文件下命令行运行"java filename [指定参数]"进行传参 
		
		String infile = new String();
		String outfile = new String();
		int weight;
		int member;
		int number;
		
		commandline cml= new commandline(args);
		
		infile = cml.infile;
		outfile = cml.outfile;
		weight = Integer.parseInt(cml.weight);
		member = Integer.parseInt(cml.member);
		number = Integer.parseInt(cml.number);
		
		Infile in = new Infile();
		in.readfile(infile, weight, member, number);
		in.writefile(outfile,number);
		
//		System.out.println(infile);
//		System.out.println(outfile);
//		System.out.println(weight);
//		System.out.println(member);
//		System.out.println(number);
		
	}

}
