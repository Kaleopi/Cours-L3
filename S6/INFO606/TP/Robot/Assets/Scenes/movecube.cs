using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class movecube : MonoBehaviour
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
            Vector3 cubePosition = transform.position;
            cubePosition.z += 0.1f;
            transform.position = cubePosition;
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            Vector3 cubePosition = transform.position;
            cubePosition.z += -0.1f;
            transform.position = cubePosition;
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            Vector3 cubePosition = transform.position;
            cubePosition.x += -0.1f;
            transform.position = cubePosition;
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            Vector3 cubePosition = transform.position;
            cubePosition.x += 0.1f;
            transform.position = cubePosition;
        }
    }
}
