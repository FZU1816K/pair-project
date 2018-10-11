public class details {
	private String paperID;
	private String paperUrl;
	private String paperTitle;
	private String paperAuthors;
	private String paperAbstract;
	private String paperType;
	private String paperMonth;
	
	public void init() {
		this.paperID = "";
		this.paperUrl="";
		this.paperTitle="";
		this.paperAuthors="";
		this.paperAbstract="";
		this.paperType="Poster";
		this.paperMonth="";
	}
	
	public void setPaperId(String id){
		this.paperID=id;
	}
	
	public void setPaperUrl(String url) {
		this.paperUrl=url;
	}
	
	public void setPaperTitle(String title){
		this.paperTitle=title;
	}
	
	public void setPaperType(String type){
		this.paperType=type;
	}
	
	public void setPaperMonth(String month) {
		this.paperMonth = month;
	}
	
	public void setPaperAbstract(String abs) {
		this.paperAbstract = abs;
	}
	
	public void setPaperAuthors(String authors) {
		this.paperAuthors = authors;
	}

	public String getPaperId() {
		return paperID;
	}
	
	public String getPaperTitle() {
		return paperTitle;
	}
	
	public String getPaperType() {
		return paperType;
	}
	
	public String getPaperMonth() {
		return paperMonth;
	}
	
	public String getPaperUrl() {
		return paperUrl;
	}

	public String getPaperAbstract() {
		return paperAbstract;
	}

	public String getPaperAuthors() {
		return paperAuthors;
	}

	
	
}