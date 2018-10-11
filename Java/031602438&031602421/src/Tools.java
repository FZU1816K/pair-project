import java.util.*;

public class Tools {

    public Map<String,Integer> wordCount =new HashMap<String,Integer>();//单词统计
    public Map<String,Integer> phraseCount =new HashMap<String,Integer>();//词组统计

    /**
     * 统计有效行数
     * @param data
     * @return
     */
    public int LineCount(String data){
        int lines=0;
        boolean flag = false;
        for(int i=0;i<data.length();i++){
            if(data.charAt(i)>' '){
                flag=true;
            }
            else if(data.charAt(i)=='\n'){
                if(flag) {
                    lines++;
                    flag=false;
                }
            }
        }
        if(flag)
            lines++;
        return lines;
    }
    /**
     * 词频统计
     * @param data
     * @return amount
     */
    public int WordCount(String data){

        int amount = 0;
        String data_l = data.toLowerCase(); // 全部字母转小写.
        String regex = "[^0-9a-zA-Z]"; //正则表达式，过滤非字母数字字符。
        data_l = data_l.replaceAll(regex, " "); //清洗文本。
        StringTokenizer words = new StringTokenizer(data_l); //分割文本成单词。
        try {
            while (words.hasMoreTokens()) {
                String word = words.nextToken();
                if (word.length() >= 4 && Character.isLetter(word.charAt(0)) && Character.isLetter(word.charAt(1)) && Character.isLetter(word.charAt(2)) && Character.isLetter(word.charAt(3))) {  //判断单词前4个是否为字母
                    amount++;
                    if (!wordCount.containsKey(word)) {
                        wordCount.put(word, new Integer(1));
                    } else {
                        int count = wordCount.get(word) + 1;
                        wordCount.put(word, count);
                    }
                }

            }
        }catch (Exception e){
            System.out.println("词频统计报错：");
            System.out.println(e.getMessage());
        }
        return amount;
    }

    /*
     * 统计单词数
     * 参数 一个字符串
     *  ty 参数当ty==1 权重为10  ty==0 权重为1
     *  return 单词数量
     */
    public int CountforWord(String ss,int ty){
        int ant=0;
        ss = ss.toLowerCase();
        String regex = "[^0-9a-zA-Z]";//分隔符集合
        ss = ss.replaceAll(regex, " ");
        StringTokenizer words = new StringTokenizer(ss); //分割文本成单词。
        try {
            while (words.hasMoreTokens()) {
                String word = words.nextToken();
                if (word.length() >= 4 && Character.isLetter(word.charAt(0)) && Character.isLetter(word.charAt(1)) && Character.isLetter(word.charAt(2)) && Character.isLetter(word.charAt(3))) {  //判断单词前4个是否为字母
                    ant++;
                    if (!wordCount.containsKey(word)) {

                        wordCount.put(word, new Integer(ty==1 ? 10:1));
                    } else {
                        int count = wordCount.get(word) + (ty==1 ? 10:1);
                        wordCount.put(word, count);
                    }
                }
            }
        }catch (Exception e){
            System.out.println("词频统计报错：");
            System.out.println(e.getMessage());
        }
        return ant;
    }
    /*
     * 统计词组
     * 参数 字符串 ant:词组的单词数  ty权重类型
     *  ty 参数当ty==1 权重为10  ty==0 权重为1
     */
    public void CountforPhrase(String ss,int ant,int ty){
        ss = ss.toLowerCase();
        ss = ss.replaceAll("\n","");
        StringBuilder mid=new StringBuilder();//分隔符
        StringBuilder wword=new StringBuilder();//单词拼接
        Queue<String> que1=new LinkedList<String>();//用于存储词组单词
        Queue<String> que2=new LinkedList<String>();//用于存储分隔符
        String feng=",./;'[] \\<>?:\"{}|`~!@#$%^&*()_+-=";//分隔符集合
        StringTokenizer words = new StringTokenizer(ss,feng,true); //分割文本成单词。
        try {
            while (words.hasMoreTokens()) {
                String word =words.nextToken();
                if (word.length() >= 4 && Character.isLetter(word.charAt(0)) && Character.isLetter(word.charAt(1)) && Character.isLetter(word.charAt(2)) && Character.isLetter(word.charAt(3))) {  //判断单词前4个是否为字母

                    que2.offer(mid.toString());
                    mid.delete(0,mid.length());
                    que1.offer(word);
                    if(que1.size()>=ant){//达到词组单词数量
                        int cnt=0;
                        wword.delete(0,wword.length());
                        for(String w:que1){
                            wword.append(w);
                            cnt++;
                            if(que2.size()>cnt)
                            {
                                String tmp=((LinkedList<String>) que2).get(cnt);//取出中间的分隔符
                                wword.append(tmp);//拼接
                            }
                        }
                        //最后生成正确的wword 词组
                        // 进行统计操作
                        if(!phraseCount.containsKey(wword.toString()))
                        {
                            phraseCount.put(wword.toString(),new Integer( ty==1 ? 10:1 ));
                        }
                        else{
                            int count=phraseCount.get(wword.toString()) + (ty==1 ? 10:1);
                            phraseCount.put(wword.toString(),count);
                        }
                        que1.remove();
                        que2.remove();
                    }
                }
                else if(word.length()!=1){//不符合条件 将其前面的都删除
                    que1.clear();
                    que2.clear();
                }else if(word.length()==1 && !(Character.isLetter(word.charAt(0)))){//判断是否为分隔符
                    mid.append(word);
                }
            }
        }catch (Exception e){
            System.out.println("词频统计报错：");
            System.out.println(e.getMessage());
        }

    }
    /**
     *  词频排序 返回列表
     * @return list
     */
    public List<HashMap.Entry<String, Integer>> getSortList(){

        List<HashMap.Entry<String, Integer>> wordList = new ArrayList<>();

        for(Map.Entry<String, Integer> entry : phraseCount.entrySet()){
            wordList.add(entry);
        }
        Comparator<Map.Entry<String, Integer>> cmp = new Comparator<Map.Entry<String, Integer>>(){
            @Override
            public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
                if(o1.getValue().equals(o2.getValue()))
                    return o1.getKey().compareTo(o2.getKey());     //值相同 按键返回字典序.
                return o2.getValue()-o1.getValue();
            }
            //逆序（从大到小）排列，正序为“return o1.getValue()-o2.getValue"
        };
        wordList.sort(cmp);
        return wordList;
    }

}
