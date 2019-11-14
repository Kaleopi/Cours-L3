import org.json.*;

public class GPS{
    protected String longitude;
    protected String latitude;


    public GPS() {
        this.longitude = "NaN";
        this.latitude = "NaN";
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
    public String toString() {
        return "{" +
            " longitude='" + getLongitude() + "'" +
            ", latitude='" + getLatitude() + "'" +
            "}";
    }

    public JSONObject toJSON() {
        JSONObject j = new JSONObject(this);
        return j;
    }

}