import org.json.*;

class Certificat extends Serializable{
    protected String nomMachine;
    protected String ipMachine;
    protected String clePublique;
    protected String nomAutorite;
    protected String ipAutorite;

    public Certificat() {
    }

    public Certificat(String nomMachine, String ipMachine, String clePublique, String nomAutorite, String ipAutorite) {
        this.nomMachine = nomMachine;
        this.ipMachine = ipMachine;
        this.clePublique = clePublique;
        this.nomAutorite = nomAutorite;
        this.ipAutorite = ipAutorite;
    }

    public String getNomMachine() {
        return this.nomMachine;
    }

    public void setNomMachine(String nomMachine) {
        this.nomMachine = nomMachine;
    }

    public String getIpMachine() {
        return this.ipMachine;
    }

    public void setIpMachine(String ipMachine) {
        this.ipMachine = ipMachine;
    }

    public String getClePublique() {
        return this.clePublique;
    }

    public void setClePublique(String clePublique) {
        this.clePublique = clePublique;
    }

    public String getNomAutorite() {
        return this.nomAutorite;
    }

    public void setNomAutorite(String nomAutorite) {
        this.nomAutorite = nomAutorite;
    }

    public String getIpAutorite() {
        return this.ipAutorite;
    }

    public void setIpAutorite(String ipAutorite) {
        this.ipAutorite = ipAutorite;
    }

    public Certificat nomMachine(String nomMachine) {
        this.nomMachine = nomMachine;
        return this;
    }

    public Certificat ipMachine(String ipMachine) {
        this.ipMachine = ipMachine;
        return this;
    }

    public Certificat clePublique(String clePublique) {
        this.clePublique = clePublique;
        return this;
    }

    public Certificat nomAutorite(String nomAutorite) {
        this.nomAutorite = nomAutorite;
        return this;
    }

    public Certificat ipAutorite(String ipAutorite) {
        this.ipAutorite = ipAutorite;
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Certificat)) {
            return false;
        }
        Certificat certificat = (Certificat) o;
        return Objects.equals(nomMachine, certificat.nomMachine) && Objects.equals(ipMachine, certificat.ipMachine) && Objects.equals(clePublique, certificat.clePublique) && Objects.equals(nomAutorite, certificat.nomAutorite) && Objects.equals(ipAutorite, certificat.ipAutorite);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nomMachine, ipMachine, clePublique, nomAutorite, ipAutorite);
    }

    @Override
    public String toString() {
        return "{" +
            " nomMachine='" + getNomMachine() + "'" +
            ", ipMachine='" + getIpMachine() + "'" +
            ", clePublique='" + getClePublique() + "'" +
            ", nomAutorite='" + getNomAutorite() + "'" +
            ", ipAutorite='" + getIpAutorite() + "'" +
            "}";
    }

    public JSONObject toJSON(){
        JSONOBject json = new JSONObject(this);
        return json;
    }

}