package HomeWorkAgain.entity;

import java.util.Comparator;
import java.util.Map;

public class ResultComparator implements Comparator<Map.Entry<String, Integer>> {
    @Override
    public int compare(Map.Entry<String, Integer> o1, Map.Entry<String, Integer> o2) {
        if (o1.getValue().equals(o2.getValue())) {
            return o1.getKey().compareTo(o2.getKey());
        }
        return o2.getValue().compareTo(o1.getValue());
    }
}
