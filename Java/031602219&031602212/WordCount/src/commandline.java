import org.apache.commons.cli.Options;
import org.apache.commons.cli.BasicParser;
import org.apache.commons.cli.ParseException;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.CommandLine;


@SuppressWarnings("deprecation")
public class commandline {	
	
	public String infile = new String();
	public String outfile = new String();
	public String weight = new String();
	public String member = new String();
	public String number = new String();
	
	public commandline(String[] args) {
		
		CommandLineParser parser = new BasicParser();
		Options options = new Options();
		
		options.addOption("h", "help", false,"Helps About this Command");
		options.addOption("i", "input", true, "Input this file");
		options.addOption("o", "output", true, "Output this file");
		options.addOption("w", "weight", true, "Weight of the word");
		options.addOption("m", "members", true, "Members of count words");
		options.addOption("n", "number", true, "Numbers of output words");
		
		try {
			CommandLine commandline = parser.parse(options, args);
			if(commandline.hasOption("h")) {
				HelpFormatter formatter = new HelpFormatter();
				formatter.printHelp("CommandLineParameters",options);
			}
			if(commandline.hasOption("i")) {
				infile =  commandline.getOptionValue("i");
			}
			if(commandline.hasOption("o")) {
				outfile =  commandline.getOptionValue("o");
			}
			if(commandline.hasOption("w")) {
				weight =  commandline.getOptionValue("w");
			}
			if(commandline.hasOption("o")) {
				member =  commandline.getOptionValue("m");
			}
			if(commandline.hasOption("o")) {
				number =  commandline.getOptionValue("n");
			}
		} catch (ParseException e) {
			e.printStackTrace();
		}
	}
}
