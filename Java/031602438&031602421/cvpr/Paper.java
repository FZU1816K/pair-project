import java.util.List;

public class Paper {
    String type;
    String title;
    List<Author> authors;
    String abstracts;
    String pdf_link;
    public Paper(String type,String title,List<Author> authors,String abstracts,String pdf_link){
        this.type = type;
        this.title = title;
        this.abstracts = abstracts;
        this.authors = authors;
        this.pdf_link = pdf_link;
    }
    public Paper(){

    }
    public String getAbstracts() {
        return abstracts;
    }

    public List<Author> getAuthors() {
        return authors;
    }

    public String getPdf_link() {
        return pdf_link;
    }

    public String getTitle() {
        return title;
    }

    public String getType() {
        return type;
    }

    public void setAbstracts(String abstracts) {
        this.abstracts = abstracts;
    }

    public void setAuthors(List<Author> authors) {
        this.authors = authors;
    }

    public void setPdf_link(String pdf_link) {
        this.pdf_link = pdf_link;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setType(String type) {
        this.type = type;
    }
    public String getAuthor(){
        StringBuilder str = new StringBuilder();
        for(Author a:authors){
            str.append(a.getName());
            str.append(",");
            str.append(a.getBelong());
            str.append(";");
        }
        return str.toString();
    }
}
