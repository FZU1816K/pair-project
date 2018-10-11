public class  Author{
    String name;
    String belong;
    int symbolSize;
    public Author(){
    }
    public Author(String name,String belong){
        this.name = name;
        this.belong = belong;
        this.symbolSize = 10;
    }
    public String getBelong() {
        return belong;
    }

    public String getName() {
        return name;
    }

    public void setBelong(String belong) {
        this.belong = belong;
    }

    public void setName(String name) {
        this.name = name;
    }
}
