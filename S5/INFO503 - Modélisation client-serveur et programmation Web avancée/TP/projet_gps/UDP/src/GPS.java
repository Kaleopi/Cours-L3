

public class GPS{
    protected String longitude;
    protected String latitude;


    public GPS() {
    }

    public GPS(String longitude, String latitude) {
        this.longitude = longitude;
        this.latitude = latitude;
    }
    public String getLongitude() {
        return this.longitude;
    }
    public void setLongitude(String longitude) {
        this.longitude = longitude;
    }
    public String getLatitude() {
        return this.latitude;
    }
    public void setLatitude(String latitude) {
        this.latitude = latitude;
    }


    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof GPS)) {
            return false;
        }
        GPS gPS = (GPS) o;
        return Objects.equals(longitude, gPS.longitude) && Objects.equals(latitude, gPS.latitude);
    }

    @Override
    public int hashCode() {
        return Objects.hash(longitude, latitude);
    }

    @Override
    public String toString() {
        return "{" +
            " longitude='" + getLongitude() + "'" +
            ", latitude='" + getLatitude() + "'" +
            "}";
    }

}