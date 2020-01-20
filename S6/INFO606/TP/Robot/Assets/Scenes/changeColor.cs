using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class changeColor : MonoBehaviour
{
    GameObject RedQuad;
    GameObject BlueQuad;
    GameObject GreenQuad;
    Renderer CubeRenderer;
    // Start is called before the first frame update
    void Start()
    {
        RedQuad = GameObject.FindGameObjectWithTag("RedQuad");
        BlueQuad = GameObject.FindGameObjectWithTag("BlueQuad");
        GreenQuad = GameObject.FindGameObjectWithTag("GreenQuad");
        CubeRenderer = GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 RedQuadPos = RedQuad.transform.position;
        Vector3 BlueQuadPos = BlueQuad.transform.position;
        Vector3 GreenQuadPos = GreenQuad.transform.position;
        Vector3 RedQuadScale = RedQuad.transform.localScale;
        Vector3 BlueQuadScale = BlueQuad.transform.localScale;
        Vector3 GreenQuadScale = GreenQuad.transform.localScale;

        float xminRed = RedQuadPos.x - RedQuadScale.x / 2;
        float xmaxRed = RedQuadPos.x + RedQuadScale.x / 2;
        float xminBlue = BlueQuadPos.x - BlueQuadScale.x / 2;
        float xmaxBlue = BlueQuadPos.x + BlueQuadScale.x / 2;
        float xminGreen = GreenQuadPos.x - GreenQuadScale.x / 2;
        float xmaxGreen = GreenQuadPos.x + GreenQuadScale.x / 2;

        float zminRed = RedQuadPos.z - RedQuadScale.y / 2;
        float zmaxRed = RedQuadPos.z + RedQuadScale.y / 2;
        float zminBlue = BlueQuadPos.z - BlueQuadScale.y / 2;
        float zmaxBlue = BlueQuadPos.z + BlueQuadScale.y / 2;
        float zminGreen = GreenQuadPos.z - GreenQuadScale.y / 2;
        float zmaxGreen = GreenQuadPos.z + GreenQuadScale.y / 2;

        if ((transform.position.x > xminRed && transform.position.x < xmaxRed) && (transform.position.z > zminRed && transform.position.z < zmaxRed))
        {

            CubeRenderer.material.SetColor("_Color", Color.red);

        }
        else if ((transform.position.x > xminBlue && transform.position.x < xmaxBlue) && (transform.position.z > zminBlue && transform.position.z < zmaxBlue))
        {

            CubeRenderer.material.SetColor("_Color", Color.blue);

        }
        else if ((transform.position.x > xminGreen && transform.position.x < xmaxGreen) && (transform.position.z > zminGreen && transform.position.z < zmaxGreen))
        {

            CubeRenderer.material.SetColor("_Color", Color.green);

        }
        else
        {
            CubeRenderer.material.SetColor("_Color", Color.white);
        }
    }
}
