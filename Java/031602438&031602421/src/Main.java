import java.io.File;

public class Main{
    public static void main(String[] args) {
        String inputFile = null;
        String outputFile = null;
        int weight = 0;
        int m = 1;
        int n = 10;
        for(int i=0;i<args.length;i++){
            switch(args[i]){
                case "-i":
                    inputFile = args[++i];
                    break;
                case "-o":
                    outputFile = args[++i];
                    break;
                case "-w":
                    if(args[++i].equals("0")){
                        weight=0;
                    }else{
                        weight=1;
                    }
                    break;
                case "-m":
                    m = Integer.parseInt(args[++i]);
                    break;
                case "-n":
                    n = Integer.parseInt(args[++i]);
                    break;
            }
        }
        if(inputFile!=null && outputFile!=null){
            Tools tool = new Tools();
            FileRead fileRead = new FileRead();
            fileRead.Input(new File(inputFile));


            int characters = 0;
            int wordCounts = 0;
            //权重为true title：1 abstract：0 权重为false title：0 abstract：0
            for(String title: fileRead.getTitles()) {
                title = title.replaceAll("\r\n","\n");
                title = title.replaceAll("[^(\\x00-\\x7f)]","");
                characters += title.length();
                wordCounts += tool.CountforWord(title,weight);
                tool.CountforPhrase(title,m,weight);

            }
            for(String abs: fileRead.getAbstracts()){
                abs = abs.replaceAll("\r\n","\n");
                abs = abs.replaceAll("[^(\\x00-\\x7f)]","");
                characters += abs.length();
                wordCounts += tool.CountforWord(abs,0);
                tool.CountforPhrase(abs,m,0);

            }

            fileRead.Output(characters,wordCounts,fileRead.getTitles().size()*2,tool.getSortList(),outputFile,n);
        }else{
            System.out.println("必需参数不能为空！");
        }

    }
}