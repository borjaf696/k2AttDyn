import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;


// Sustituye los separadores de ; por # y comprueba que sea un separador que no se use como texto
public class cleanerWiki {


	public static void clean(String path, String outPath) throws IOException{
		// Lectura del fichero
		String linea;
		File file = new File(path);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);

		
		FileWriter fw = new FileWriter(new File(outPath));
		BufferedWriter bw = new BufferedWriter(fw);
		
		int i=0;
		//Leemos las querys y las metemos en ambas hashes
		while ((linea = br.readLine()) != null) {
			if (linea.indexOf("##")>0){
				System.out.println("Separador inválido: aparece en línea "+i);
				break;
			}
			i++;
			int primera = linea.indexOf(";");
			String primerItem = linea.substring(0,primera);
			int segunda = linea.indexOf(";",primera+1);
			String segundoItem = linea.substring(primera+1,segunda);
			String tercerItem = linea.substring(segunda);
			tercerItem = tercerItem.substring(1, tercerItem.length()-1);
			bw.write(primerItem+"##"+segundoItem+"##"+tercerItem+"##\n");
			i++;
		}
		bw.close();
	}

	public static void main(String [] args) throws IOException {
		path 	= new String("/home/sandra/2014/investigacion/attGraphs/datasets/wikipedia/rdbms_refs_title.csv");
		dividir(path,outPath);
	}

}
