using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class changeColor : MonoBehaviour
{
    GameObject RedQuad;
    GameObject RedQuad1;
    GameObject RedQuad2;
    GameObject RedQuad3;

    Renderer CubeRenderer;
    // Start is called before the first frame update
    void Start()
    {
        RedQuad = GameObject.FindGameObjectWithTag("RedQuad");
        RedQuad1 = GameObject.FindGameObjectWithTag("RedQuad1");
        RedQuad2 = GameObject.FindGameObjectWithTag("RedQuad2");
        RedQuad3 = GameObject.FindGameObjectWithTag("RedQuad3");

        CubeRenderer = GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 RedQuadPos = RedQuad.transform.position;
        Vector3 RedQuadScale = RedQuad.transform.localScale;

        Vector3 RedQuadPos1 = RedQuad1.transform.position;
        Vector3 RedQuadScale1 = RedQuad1.transform.localScale;

        Vector3 RedQuadPos2 = RedQuad2.transform.position;
        Vector3 RedQuadScale2 = RedQuad2.transform.localScale;

        Vector3 RedQuadPos3 = RedQuad3.transform.position;
        Vector3 RedQuadScale3 = RedQuad3.transform.localScale;





        float xminRed = RedQuadPos.x - RedQuadScale.x / 2;
        float xmaxRed = RedQuadPos.x + RedQuadScale.x / 2;

        float xminRed1 = RedQuadPos1.x - RedQuadScale1.x / 2;
        float xmaxRed1 = RedQuadPos1.x + RedQuadScale1.x / 2;

        float xminRed2 = RedQuadPos2.x - RedQuadScale2.x / 2;
        float xmaxRed2 = RedQuadPos2.x + RedQuadScale2.x / 2;

        float xminRed3 = RedQuadPos3.x - RedQuadScale3.x / 2;
        float xmaxRed3 = RedQuadPos3.x + RedQuadScale3.x / 2;
        /////
        /////
        float zminRed = RedQuadPos.z - RedQuadScale.y / 2;
        float zmaxRed = RedQuadPos.z + RedQuadScale.y / 2;


        float zminRed1 = RedQuadPos1.z - RedQuadScale1.y / 2;
        float zmaxRed1 = RedQuadPos1.z + RedQuadScale1.y / 2;


        float zminRed2 = RedQuadPos2.z - RedQuadScale2.y / 2;
        float zmaxRed2 = RedQuadPos2.z + RedQuadScale2.y / 2;


        float zminRed3 = RedQuadPos3.z - RedQuadScale3.y / 2;
        float zmaxRed3 = RedQuadPos3.z + RedQuadScale3.y / 2;




        if ((transform.position.x > xminRed && transform.position.x < xmaxRed) && (transform.position.z > zminRed && transform.position.z < zmaxRed)||(transform.position.x > xminRed1&& transform.position.x < xmaxRed1) && (transform.position.z > zminRed1 && transform.position.z < zmaxRed1)|| (transform.position.x > xminRed2 && transform.position.x < xmaxRed2) && (transform.position.z > zminRed2 && transform.position.z < zmaxRed2)||(transform.position.x > xminRed3 && transform.position.x < xmaxRed3) && (transform.position.z > zminRed3 && transform.position.z < zmaxRed3))
        {

            CubeRenderer.material.SetColor("_Color", Color.red); //Le cube devient rouge au dessus du robot qui a perdu

        }

        else
        {
            CubeRenderer.material.SetColor("_Color", Color.green); 
        }
    }
}
