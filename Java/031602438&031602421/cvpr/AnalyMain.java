import com.google.gson.Gson;
import org.omg.Messaging.SYNC_WITH_TRANSPORT;

import java.io.*;
import java.util.*;

import static java.io.FileDescriptor.out;

public class AnalyMain {


    public static void main(String[] args){
        Analy analy = new Analy();
        FileRead fileRead = new FileRead();
        //按顺序执行 读csv -> 然后匹配
        analy.readCsv();
        analy.matchCsv();
        ArrayList<Paper> papers = analy.getPapers();
        Gson gson = new Gson();
        List<String> author = new ArrayList<>();
        for(Paper p:papers){
            for(Author a:p.getAuthors()){
                author.add(gson.toJson(a));
            }
        }
        System.out.println("====全部作者json信息====");
        //System.out.println(gson.toJson(author));
        //fileRead.Write(gson.toJson(author),"AuthorList.json");
        System.out.println("************************");
        List<String> friendList = new ArrayList<>();
        for(Paper p:papers){
            List<Author> authorList = p.getAuthors();
            for(int i=0;i<authorList.size();i++){
                for(int j=i+1;j<authorList.size();j++){
                    Friend friend = new Friend(authorList.get(i).getName(),authorList.get(j).getName());
                    friendList.add(gson.toJson(friend));
                }
            }
        }
        System.out.println("====全部作者关系列表====");
        //System.out.println(gson.toJson(friendList));
        //fileRead.Write(gson.toJson(friendList),"FriendList.json");
        System.out.println("************************");

        Map<String,Integer> authorMap = new HashMap<>();
        for(Paper p:papers){
            for(Author a:p.getAuthors()){
                if(!authorMap.containsKey(a.getName())){
                    authorMap.put(a.getName(),1);
                }else{
                    authorMap.put(a.getName(),authorMap.get(a.getName())+1);
                }
            }
        }

        //输出 有5篇论文以上的作者
        for(Map.Entry<String, Integer> entry : authorMap.entrySet()){
            if(entry.getValue()>5){
                //System.out.println("'"+entry.getKey()+"',");
            }

        }
        //=======================================================
        int Poster=0;
        int Oral=0;
        int Spotlight=0;
        for(Paper p:papers){
            if(p.getType().equals("Spotlight")){
                Spotlight++;
            }else if(p.getType().equals("Oral")) {
                Oral++;
            }else if(p.getType().equals("Poster")){
                Poster++;
            }
        }
        //System.out.println("Poster:"+Poster+" Oral:"+Oral+" Spotlight:"+Spotlight);
        Map<String, Integer> cityMap = new HashMap<>();
        for(Paper p:papers){
            for(Author a:p.getAuthors()){
                if(!cityMap.containsKey(a.getBelong())){
                    cityMap.put(a.getBelong(),1);
                }else{
                    cityMap.put(a.getBelong(),cityMap.get(a.getBelong())+1);
                }
            }
        }
        // 输出拥有论文篇数的地方
        for(Map.Entry<String, Integer> entry : authorMap.entrySet()){
            if(entry.getValue()>5){
                //System.out.println("'"+entry.getKey()+"',");
                System.out.println(entry.getValue()+",");
            }
        }
    }
}

