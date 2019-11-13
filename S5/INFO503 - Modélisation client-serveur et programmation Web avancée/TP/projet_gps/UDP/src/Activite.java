
public class Activite {
    protected String idSportif;
    protected Date heureDeb;
    protected Date heureFin;
    protected String sport;
    protected GPS coords;


    public Activite() {
    }

    public Activite(String idSportif, Date heureDeb, Date heureFin, String sport, GPS coords) {
        this.idSportif = idSportif;
        this.heureDeb = heureDeb;
        this.heureFin = heureFin;
        this.sport = sport;
        this.coords = coords;
    }

    public String getIdSportif() {
        return this.idSportif;
    }

    public void setIdSportif(String idSportif) {
        this.idSportif = idSportif;
    }

    public Date getHeureDeb() {
        return this.heureDeb;
    }

    public void setHeureDeb(Date heureDeb) {
        this.heureDeb = heureDeb;
    }

    public Date getHeureFin() {
        return this.heureFin;
    }

    public void setHeureFin(Date heureFin) {
        this.heureFin = heureFin;
    }

    public String getSport() {
        return this.sport;
    }

    public void setSport(String sport) {
        this.sport = sport;
    }

    public GPS getCoords() {
        return this.coords;
    }

    public void setCoords(GPS coords) {
        this.coords = coords;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Activite)) {
            return false;
        }
        Activite activite = (Activite) o;
        return Objects.equals(idSportif, activite.idSportif) && Objects.equals(heureDeb, activite.heureDeb) && Objects.equals(heureFin, activite.heureFin) && Objects.equals(sport, activite.sport) && Objects.equals(coords, activite.coords);
    }

    @Override
    public int hashCode() {
        return Objects.hash(idSportif, heureDeb, heureFin, sport, coords);
    }

    @Override
    public String toString() {
        return "{" +
            " idSportif='" + getIdSportif() + "'" +
            ", heureDeb='" + getHeureDeb() + "'" +
            ", heureFin='" + getHeureFin() + "'" +
            ", sport='" + getSport() + "'" +
            ", coords='" + getCoords() + "'" +
            "}";
    }

}