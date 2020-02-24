using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class changeCamera : MonoBehaviour
{

    GameObject MainCamera;
    GameObject SecondCamera;
    GameObject Robot; //sumo 1
    GameObject Robot2; //sumo 2
    GameObject Cube;
    GameObject spot;
    GameObject spot1;
    GameObject spot2;
    Vector3 offsetMain;
    Vector3 offsetCube;
    Vector3 offsetRobot;
    Vector3 offsetspot;
    Vector3 offsetspot1;
    Vector3 offsetspot2;
    Transform target;
    float smooth = 5.0f;
    float tiltAngle = 60.0f;
    // Start is called before the first frame update
    bool anim = false;
    bool lightsout = false;
    bool flashlight = false;
    void Start()
    {
        MainCamera = GameObject.FindGameObjectWithTag("MainCamera");
        Robot = GameObject.FindGameObjectWithTag("Robot");
        Robot2 = GameObject.FindGameObjectWithTag("Robot2");
        Cube = GameObject.FindGameObjectWithTag("Cube");
        spot = GameObject.FindGameObjectWithTag("spot");
        spot1 = GameObject.FindGameObjectWithTag("spot1");
        spot2 = GameObject.FindGameObjectWithTag("spot2");
        MainCamera.SetActive(true);
        offsetspot = spot.transform.position - Robot.transform.position;
        offsetspot1 = spot1.transform.position - Cube.transform.position;
        offsetspot2 = spot2.transform.position - MainCamera.transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Keypad1))
        {
            MainCamera.SetActive(true);
            SecondCamera.SetActive(false);
        }
        if(Input.GetKeyDown(KeyCode.Keypad2)){
            MainCamera.SetActive(false);
            SecondCamera.SetActive(true);
        }

        if (Input.GetKeyDown(KeyCode.F))
        {
            if (flashlight)
            {
                flashlight = false;
                spot.SetActive(true);
            }
            else
            {
                flashlight = true;
                spot.SetActive(false);
            }
        }
        if (Input.GetKeyDown(KeyCode.G))
        {
            if (lightsout)
            {
                lightsout = false;
                spot.SetActive(true);
                spot1.SetActive(true);
                spot2.SetActive(true);
            }
            else
            {
                lightsout = true;
                spot.SetActive(false);
                spot1.SetActive(false);
                spot2.SetActive(false);
            }
        }
    }
    void LateUpdate() {
        spot1.transform.LookAt(Robot.transform);
        spot2.transform.LookAt(Robot2.transform);
    }
}
