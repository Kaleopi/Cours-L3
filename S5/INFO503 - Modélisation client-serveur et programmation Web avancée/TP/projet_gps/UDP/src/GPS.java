import org.json.*;

public class GPS {
    protected String longitude;
    protected String latitude;
    protected String timestamp;

    public GPS() {
        this.longitude = "NaN";
        this.latitude = "NaN";
        this.timestamp = "NaN";
    }

    public GPS(String longitude, String latitude, String timestamp) {
        this.longitude = longitude;
        this.latitude = latitude;
        this.timestamp = timestamp;
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

    public String getTimestamp() {
        return this.timestamp;
    }

    public void setTimestamp(String timestamp) {
        this.timestamp = timestamp;
    }

    @Override
    public String toString() {
        return "{" + " longitude='" + getLongitude() + "'" + ", latitude='" + getLatitude() + "'" + ", timestamp='"
                + getTimestamp() + "'" + "}";
    }

    public JSONObject toJSON() {
        JSONObject j = new JSONObject(this);
        return j;
    }

}