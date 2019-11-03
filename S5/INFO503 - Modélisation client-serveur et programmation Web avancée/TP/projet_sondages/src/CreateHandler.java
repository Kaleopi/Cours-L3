import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.Headers;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URLDecoder;
import java.util.HashMap;
import org.json.*;

class CreateHandler implements HttpHandler {
    public void handle(HttpExchange t) {
        GestionnaireUtilisateurs gest = new GestionnaireUtilisateurs("./src/logins.json");
        // String reponse = "<!DOCTYPE html>" +
        // "<html lang=\"fr\">" +
        // "<head>" +
        // "<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\"/>" +
        // "</head>" +
        // "<body>";
        String reponse = "";
        HashMap<String, String> tabJson = new HashMap<String, String>();

        // Récupération des données
        URI requestedUri = t.getRequestURI();
        String query = requestedUri.getRawQuery();

        // Utilisation d'un flux pour lire les données du message Http
        BufferedReader br = null;
        try {
            br = new BufferedReader(new InputStreamReader(t.getRequestBody(), "utf-8"));
        } catch (UnsupportedEncodingException e) {
            System.err.println("Erreur lors de la récupération du flux " + e);
            System.exit(-1);
        }

        // Récupération des données en POST
        try {
            query = br.readLine();
        } catch (IOException e) {
            System.err.println("Erreur lors de la lecture d'une ligne " + e);
            System.exit(-1);
        }

        // Affichage des données
        if (query == null) {
            tabJson.put("code", "erreur");
            tabJson.put("message", "Aucune donnée en POST");
            JSONObject jsonO = new JSONObject(tabJson);
            // System.out.println(jsonO);
            reponse += jsonO;
        } else {
            try {
                query = URLDecoder.decode(query, "UTF-8");
                // vérification
                String[] stok;
                stok = query.split("\"");
                String mdp = stok[3];
                String login = stok[9];
                // System.out.println(login+" "+mdp);
                boolean trouve = gest.search(login, mdp);
                // System.out.println(trouve);
                if (!trouve) {
                    gest.addUser(login, mdp);
                    tabJson.put("code", "OKinscription");
                    tabJson.put("message", "Vous êtes bien inscrit !");
                    JSONObject jsonO = new JSONObject(tabJson);
                    reponse += jsonO;
                } else {
                    tabJson.put("code", "erreur");
                    tabJson.put("message", "Utilisateur déjà existant.");
                    JSONObject jsonO = new JSONObject(tabJson);
                    reponse += jsonO;
                }
            } catch (UnsupportedEncodingException io) {
                System.out.println("Erreur query");
            }
        }
        // Envoi de l'en-tête Http
        try {
            Headers h = t.getResponseHeaders();
            h.set("Content-Type", "text/html; charset=utf-8");
            t.sendResponseHeaders(200, reponse.getBytes().length);
        } catch (IOException e) {
            System.err.println("Erreur lors de l'envoi de l'en-tête : " + e);
            System.exit(-1);
        }

        // Envoi du corps (données HTML)
        try {
            OutputStream os = t.getResponseBody();
            os.write(reponse.getBytes());
            os.close();
        } catch (IOException e) {
            System.err.println("Erreur lors de l'envoi du corps : " + e);
        }
    }

}
