using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using UnityEngine.Networking;

public class InputFieldHandler : MonoBehaviour
{
    public InputField InputField;
    public InputField OutputField;

    public int ActualisationRate = 60;

    private int _NbUpdate = 0;
    private bool _HasValueChanged = false;

    void Start()
    {
        InputField.onValueChanged.AddListener(delegate { LockInput(InputField); });
    }

    void LockInput(InputField input)
	{
        _HasValueChanged = true;
	}

    void Update()
    {
        ++_NbUpdate;
        if (_NbUpdate == ActualisationRate)
        {
            _NbUpdate = 0;
            if (_HasValueChanged)
            {
                if (InputField.text.Length > 0) 
                {
                    StartCoroutine(CallAPI(InputField.text));
                }
                else if (InputField.text.Length == 0) 
                {
                    OutputField.readOnly = false;
                    OutputField.text = "";
                    OutputField.readOnly = true;
                }
            }
            _HasValueChanged = false;
        }
    }

    IEnumerator CallAPI(string textToTranslate)
    {
        WWWForm form = new WWWForm();
        form.AddField("text", textToTranslate);

        UnityWebRequest www = UnityWebRequest.Post("https://yololtranslate-api.baduit.eu/translate", form);
        yield return www.SendWebRequest();

        if (www.isNetworkError || www.isHttpError)
        {
            Debug.Log(www.error);
        }
        else
        {
            Debug.Log(www.downloadHandler.text);
            OutputField.readOnly = false;
            OutputField.text = www.downloadHandler.text;
            OutputField.readOnly = true;
        }
    }
}
