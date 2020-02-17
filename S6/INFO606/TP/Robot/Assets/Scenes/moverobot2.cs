using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class moverobot2 : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.UpArrow))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.z += 0.1f;
            transform.position = robotPosition;
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.z += -0.1f;
            transform.position = robotPosition;
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.x += -0.1f;
            transform.position = robotPosition;
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.x += 0.1f;
            transform.position = robotPosition;
        }
    }
}
