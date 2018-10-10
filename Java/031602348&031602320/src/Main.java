//package HomeWorkAgain;

import HomeWorkAgain.entity.Result;
import javafx.scene.shape.Line;

import java.io.*;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException {
        //       long start = System.currentTimeMillis();计时
        int n = 10;//提前设置N的值
        int w = 1;//权重
        int m = 1;//词组
        String name = new String();
        String resultOut = new String();
        for (int i = 0; i < args.length; i++) {//对cmd窗口输入参数进行处理
            if (args[i].equals("-i")) {
                name = args[i + 1];//输入搞定
            }
            if (args[i].equals("-o")) {
                resultOut = args[i + 1];//输出搞定
            }
            if (args[i].equals("-n")) {
                n = Integer.parseInt(args[i + 1]);//把字符串转化成数值
            }
            if (args[i].equals("-w")) {
                w = Integer.parseInt(args[i + 1]);
                switch (w) {
                    case 1:
                        w = 10;
                        break;
                    case 0:
                        w = 1;
                        break;
                }
            }
            if (args[i].equals("-m")) {
                m = Integer.parseInt(args[i + 1]);

            }
        }
        //String name = "input3.txt";
        File file = createFile(name);
        Result result = processContent(file, w, m);
        result.setOUTPUT_LIMIT(n);//传入N了


        System.out.println(result);
//        long end = System.currentTimeMillis();
        //      System.out.println("Program ends, time:" + (end - start));
        File writename = new File(resultOut);
        writename.createNewFile();
        BufferedWriter out = new BufferedWriter(new FileWriter(writename));
        out.write(String.valueOf(result));
        out.flush();
        out.close();


    }

    private static File createFile(String name) throws FileNotFoundException {
        if (name == null || name.isEmpty()) {
            System.err.println("Please Enter Right Filename!");
            return null;
        }
        File file = new File(name);
        if (!file.exists()) {
            throw new FileNotFoundException("Could not find file: " + file.getAbsolutePath());
        }
        return file;
    }

    private static Result processContent(File content, int w, int m) throws IOException {
        Result result = new Result();
        List<String> lines = Files.readAllLines(content.toPath());
        byte[] Lines = Files.readAllBytes(content.toPath());
        String contentR = new String(Lines);
        int lineCount = 0;
        for (int i = 0; i < contentR.length(); i++) {
            if (contentR.charAt(i) == '\r') {
                lineCount++;//读回车符
            }
        }
        lines.forEach(line -> {
            if (!line.trim().isEmpty()) {
                result.addALine();
            }
            int flag = 0;
            if (line.startsWith("Title: ")) {
                line = line.substring(7, line.length());//裁剪title，从第六个字符开始读
                result.setInValidWords();
                flag = 1;
            }
            if (line.startsWith("Abstract: ")) {
                line = line.substring(10, line.length());//尚未修改最后输出的值的函数
            }

            result.addCharacters(line.length());//字符提前统计
            if (m == 1) {
                List<String> validWords = Arrays.stream(line.split("[^0-9a-zA-Z]"))
                        .map(String::toLowerCase)
                        .filter(Main::isValidWord)
                        .collect(Collectors.toList());//输入有效数字放入addWords

                if (flag == 1) {
                    result.addWords(validWords, w);
                } else if (flag == 0) {
                    result.addWords(validWords, 1);
                }
            }
            /*   在这里加上m的判断*/


            if (m >= 2 && m <= 10) {
                int eachI = 0;//每行初始
                String Str = new String();
                int count = 0;
                List<String> myList = new ArrayList<String>();
                List<String> anotherSign = new ArrayList<String>();
                List<String> anotherword = new ArrayList<String>();
                List<String> AllSign = Arrays.stream(line.split("[0-9a-zA-Z]"))
                        .collect(Collectors.toList());
                for (int z = 0; z < AllSign.size(); z++) {
                    if (!AllSign.get(z).equals("")) {
                        anotherSign.add(AllSign.get(z));
                    }
                }
                List<String> AllWords = Arrays.stream(line.split("[^0-9a-zA-Z]"))
                        .map(String::toLowerCase)
                        .collect(Collectors.toList());//全部可能的单词
                for (int t = 0; t <AllWords.size(); t++) {
                    if (!AllWords.get(t).equals("")) {
                        anotherword.add(AllWords.get(t));//重新整合字符串数组
                    }
                }

                if(anotherword.size()<m){
                    return;   //>m后处理溢出
                }
                else {
                    for (eachI = 0; eachI < anotherword.size(); eachI++) {
                        if (isValidWord(anotherword.get(eachI))) {
                            if (count < m - 1) {
                                if(eachI==anotherword.size()-1) {
                                    break;
                                }else{
                                    Str += (anotherword.get(eachI) + anotherSign.get(eachI));//Sign数组溢出
                                    count++;
                                }
                            } else {
                                Str += anotherword.get(eachI);
                                // System.out.println("EachI"+":"+eachI);//delete
//                                System.out.println("Str"+":"+Str);//delete
//                                System.out.println("Sing:"+anotherSign.size());
                                myList.add(Str);//加入list
                                count = 0;
                                Str = "";
                                if (eachI == anotherword.size() - 1) {
                                    break;
                                } else {
                                    eachI = eachI - m + 1;
                                }

                            }
                        } else {
                            Str ="";
                            count = 0;
                        }
                    }
                }
                if (flag == 1) {
                    result.addWords(myList, w);
                } else if (flag == 0) {
                    result.addWords(myList, 1);
                }


            }
            /* */
        });

        result.addCharacters(lineCount);
        return result;

    }


    private static boolean isValidWord(String word) {
        if (word == null || word.length() < 4) {
            return false;
        }
        return Character.isAlphabetic(word.charAt(0)) &&
                Character.isAlphabetic(word.charAt(1)) &&
                Character.isAlphabetic(word.charAt(2)) &&
                Character.isAlphabetic(word.charAt(3));
    }
}
