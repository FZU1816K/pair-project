package HomeWorkAgain.entity;

import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Result {
    private int OUTPUT_LIMIT;
    private int characterCount;
    private int wordCount;
    private int lineCount;
    private int inValidWords;//记录Title数
    private int w;
    private int flag;
    private Map<String, Integer> words = new HashMap<>();

    public void setOUTPUT_LIMIT(int output_LIMIT) {
        this.OUTPUT_LIMIT = output_LIMIT;
    } //得从外部导入

    public int getCharacterCount() {
        return characterCount;
    }


    public void setCharacterCount(int characterCount) {
        this.characterCount = characterCount;
    }

    public void setFlag(int Flag) {
        this.flag = Flag;
    }

    public void setInValidWords() {
        inValidWords++;
    }//

    public int getWordCount() {
        return wordCount;
    }

    public void setWordCount(int wordCount) {
        this.wordCount = wordCount;
    }

    public int getLineCount() {
        return lineCount;
    }

    public void setLineCount(int lineCount) {
        this.lineCount = lineCount;
    }

    public Map<String, Integer> getWords() {
        return words;
    }

    public void setWords(Map<String, Integer> words) {
        this.words = words;
    }

    public void addWordCount(int count) {
        wordCount += count;
    }

    public void addWords(List<String> wordList,int w) {
        wordList.forEach(word -> {
            if (word == null || word.length() == 0) {
                return;
            }
            this.wordCount++;
                if (words.containsKey(word)) {
                    int value = words.get(word);
                    value += w;/*就是要对这里改*/
                    words.put(word, value);
                } else {
                words.put(word, w);
            }
        });
    }

    public List<Map.Entry<String, Integer>> getTopEntry() {
        return words.entrySet()
                .stream()
                .sorted(new ResultComparator())
                .limit(OUTPUT_LIMIT)
                .collect(Collectors.toList());
    }


    public void addALine() {
        this.lineCount++;
    }

    public void addCharacters(int count) {
        this.characterCount += count;
    }

    @Override
    public String toString() {

        return "characters: " + (characterCount - 4 * inValidWords + 2) + "\r\n" +
                "words: " + (wordCount ) + "\r\n" +
                "lines: " + (lineCount - inValidWords) + "\r\n" +       //减去无效的内容后
                entryListToString(getTopEntry());
    }


    private String entryListToString(List<Map.Entry<String, Integer>> entries) {
        StringBuilder result = new StringBuilder();
        entries.forEach(entry ->
                result.append("<").append(entry.getKey()).append(">: ").append(entry.getValue()).append("\r\n")
        );
        return result.toString();
    }

}
