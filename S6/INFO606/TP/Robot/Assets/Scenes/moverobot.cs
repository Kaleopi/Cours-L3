    using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class moverobot : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.Z))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.z += 0.1f;
            transform.position = robotPosition;
        }
        if (Input.GetKey(KeyCode.S))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.z += -0.1f;
            transform.position = robotPosition;
        }
        if (Input.GetKey(KeyCode.Q))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.x += -0.1f;
            transform.position = robotPosition;
        }
        if (Input.GetKey(KeyCode.D))
        {
            Vector3 robotPosition = transform.position;
            robotPosition.x += 0.1f;
            transform.position = robotPosition;
        }
    }
}
