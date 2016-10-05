using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections.Generic;

public enum LineMode
{
    Direct,
    Two_Step
}

public enum LinePriority
{
    X,
    Y
}

public class TalentNode : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler
{
    //Public vars
    public TalentNode m_RequiredNode;
    public string m_Title;
    public string m_Description;
    public bool m_IsActive = false;
    public int m_Points = 1;
    public int m_CurrentPoints = 0;
    public GameObject m_Line;
    public LineMode m_LineMode = LineMode.Direct;
    public LinePriority m_LinePriority = LinePriority.X;

    //Line vars
    RectTransform m_LineRect;
    GameObject m_Clone;
    Image m_LineImage;
    RectTransform m_LineRect2;
    GameObject m_Clone2;
    Image m_LineImage2;

    Color m_LineCol = Color.red;

    //Component vars
    Text m_NodeText;
    Text m_DescriptionText;
    RectTransform m_RectTransform;
    List<TalentNode> m_GoesToNodes = new List<TalentNode>();

    //Pointer vars
    bool m_IsHover = false;

	void Start()
    {
        m_RectTransform = GetComponent<RectTransform>();
        m_NodeText = GetComponentInChildren<Text>();
        m_DescriptionText = GameObject.Find("DescriptionText").GetComponent<Text>();

        if (m_RequiredNode == this)
        {
            Debug.Log("ERROR, require node is self: " + this.gameObject.name);
            m_RequiredNode = null;
        }
        else if (m_RequiredNode && m_RequiredNode.m_RequiredNode == this)
        {
            Debug.Log("ERROR, two or more nodes require eachother: " + gameObject.name + " & " + m_RequiredNode.gameObject.name);
            m_RequiredNode = null;
        }
        else if (m_RequiredNode && m_Line)
        {
            m_RequiredNode.m_GoesToNodes.Add(this);
            //Always create one line if there is a required node
            m_Clone = (GameObject)Instantiate(m_Line, transform.position, Quaternion.identity);
            m_Clone.transform.SetParent(transform.parent);
            m_Clone.transform.SetAsFirstSibling();
            m_Clone.transform.localScale = new Vector3(1, 1, 1);
            m_LineRect = m_Clone.GetComponent<RectTransform>();
            m_LineImage = m_Clone.GetComponent<Image>();

            //If mode is two-step then create another line
            if (GetLineMode().Equals(LineMode.Two_Step))
            {
                m_Clone2 = (GameObject)Instantiate(m_Line, transform.position, Quaternion.identity);
                m_Clone2.transform.SetParent(transform.parent);
                m_Clone2.transform.SetAsFirstSibling();
                m_Clone2.transform.localScale = new Vector3(1, 1, 1);
                m_LineRect2 = m_Clone2.GetComponent<RectTransform>();
                m_LineImage2 = m_Clone2.GetComponent<Image>();
            }
        }
    }

    void Update()
    {
        if (m_NodeText)
            m_NodeText.text = m_CurrentPoints + "/" + m_Points;

        if (m_IsHover)
        {
            m_DescriptionText.transform.position = transform.position + new Vector3(((m_DescriptionText.rectTransform.rect.width * ControllerTalent.m_CanvasScaleFactor) / 2)
            + ((m_RectTransform.rect.width * ControllerTalent.m_CanvasScaleFactor) / 2), 0, 0);
            m_DescriptionText.text = m_Title + "\n" + m_Description;
        }

        LineUpdate();
    }

    void LineUpdate()
    {
        //Removes/adds second line depending on what linemode is currently active
        if (GetLineMode().Equals(LineMode.Direct) && m_Clone2)
            Destroy(m_Clone2);
        if (GetLineMode().Equals(LineMode.Two_Step) && !m_Clone2)
        {
            m_Clone2 = (GameObject)Instantiate(m_Line, transform.position, Quaternion.identity);
            m_Clone2.transform.SetParent(transform.parent);
            m_Clone2.transform.SetAsFirstSibling();
            m_Clone2.transform.localScale = new Vector3(1, 1, 1);
            m_LineRect2 = m_Clone2.GetComponent<RectTransform>();
            m_LineImage2 = m_Clone2.GetComponent<Image>();
        }

        //What should happen if current linemode is direct
        if (GetLineMode().Equals(LineMode.Direct))
        {
            if (m_Clone)
            {
                Vector3 diff = m_RequiredNode.transform.position - transform.position;
                m_LineRect.sizeDelta = new Vector2(diff.magnitude / ControllerTalent.m_CanvasScaleFactor, 10);
                m_LineRect.pivot = new Vector2(0, 0.5f);
                m_LineRect.position = transform.position; //+ Vector3.Scale(new Vector3((m_RectTransform.rect.width * ControllerTalent.m_CanvasScaleFactor) / 2, 
                                                          //(m_RectTransform.rect.height * ControllerTalent.m_CanvasScaleFactor) / 2, 0), diff.normalized);
                float angle = Mathf.Atan2(diff.y, diff.x) * Mathf.Rad2Deg;
                m_LineRect.rotation = Quaternion.Euler(0, 0, angle);
            }
        }
        //What should happen if current linemode is two-step
        else if (GetLineMode().Equals(LineMode.Two_Step))
        {
            if (m_Clone && m_Clone2)
            {
                Vector3 diffX = new Vector3(m_RequiredNode.transform.position.x, 0, 0) - new Vector3(transform.position.x, 0, 0);
                Vector3 diffY = new Vector3(0, m_RequiredNode.transform.position.y, 0) - new Vector3(0, transform.position.y, 0);
                float angle = 0.0f;
                float angle2 = 0.0f;
                switch (m_LinePriority)
                {
                    case LinePriority.X:
                        //First line
                        m_LineRect.sizeDelta = new Vector2(diffX.magnitude / ControllerTalent.m_CanvasScaleFactor, 10);
                        m_LineRect.pivot = new Vector2(0, 0.5f);
                        m_LineRect.position = transform.position;
                        angle = Mathf.Atan2(0, diffX.x) * Mathf.Rad2Deg;
                        m_LineRect.rotation = Quaternion.Euler(0, 0, angle);

                        //Second line
                        m_LineRect2.sizeDelta = new Vector2(diffY.magnitude / ControllerTalent.m_CanvasScaleFactor, 10);
                        m_LineRect2.pivot = new Vector2(0, 0.5f);
                        m_LineRect2.position = transform.position + diffX;
                        angle2 = Mathf.Atan2(diffY.y, 0) * Mathf.Rad2Deg;
                        m_LineRect2.rotation = Quaternion.Euler(0, 0, angle2);
                        break;

                    case LinePriority.Y:
                        //First line
                        m_LineRect.sizeDelta = new Vector2(diffY.magnitude / ControllerTalent.m_CanvasScaleFactor, 10);
                        m_LineRect.pivot = new Vector2(0, 0.5f);
                        m_LineRect.position = transform.position;
                        angle = Mathf.Atan2(diffY.y, 0) * Mathf.Rad2Deg;
                        m_LineRect.rotation = Quaternion.Euler(0, 0, angle);

                        //Second line
                        m_LineRect2.sizeDelta = new Vector2(diffX.magnitude / ControllerTalent.m_CanvasScaleFactor, 10);
                        m_LineRect2.pivot = new Vector2(0, 0.5f);
                        m_LineRect2.position = transform.position + diffY;
                        angle2 = Mathf.Atan2(0, diffX.x) * Mathf.Rad2Deg;
                        m_LineRect2.rotation = Quaternion.Euler(0, 0, angle2);
                        break;
                }
            }
        }

        //Check what color the connecting line should have
        if (m_RequiredNode)
        {
            if (m_IsActive && m_RequiredNode.m_IsActive)
                m_LineCol = Color.green;
            else if (m_RequiredNode.m_IsActive && !m_IsActive)
                m_LineCol = Color.yellow;
            else if (!m_RequiredNode.m_IsActive && !m_IsActive)
                m_LineCol = Color.red;
        }
        //Assign color
        if (m_LineImage)
            m_LineImage.color = m_LineCol;
        if (m_LineImage2)
            m_LineImage2.color = m_LineCol;
    }

    void AddP()
    {
        if (m_CurrentPoints < m_Points)
        {
            if (ControllerTalent.GetHasPoints())
            {
                ControllerTalent.AddPoints(-1);

                if (!GetIsActive())
                    SetIsActive(true);

                m_CurrentPoints++;
            }
        }
    }

    void RemoveP()
    {
        if (m_CurrentPoints > 0)
        {
            m_CurrentPoints--;
            if (m_CurrentPoints <= 0)
            {
                if (GetIsActive())
                    SetIsActive(false);
            }
            ControllerTalent.AddPoints(1);
        }
    }

    public void ChangePoints()
    {
        if (Input.GetMouseButtonUp(0))
        {
            if (m_RequiredNode)
            {
                if (m_RequiredNode.m_IsActive)
                    AddP();
            }
            else
                AddP();
        }
        else if (Input.GetMouseButtonUp(1))
        {
            if (m_GoesToNodes.Count > 0)
            {
                bool can = true;
                for (int i = 0; i < m_GoesToNodes.Count; i++)
                {
                    if (m_GoesToNodes[i].m_IsActive)
                    {
                        can = false;
                        break;
                    }
                }
                if (can)
                    RemoveP();
            }
            else
                RemoveP();
        }
    }

    public void SetIsActive(bool state)
    {
        m_IsActive = state;
    }

    bool GetIsActive()
    {
        return m_IsActive;
    }

    public void OnPointerEnter(PointerEventData eventData)
    {
        m_IsHover = true;
        //Debug.Log("Pointer entered UI element");
    }

    public void OnPointerExit(PointerEventData eventData)
    {
        //m_DescriptionText.transform.position = Vector3.zero;
        m_DescriptionText.text = "";

        m_IsHover = false;
        //Debug.Log("Pointer left UI element");
    }

    public bool GetIsHover()
    {
        return m_IsHover;
    }

    public string GetTitle()
    {
        return m_Title;
    }

    public string GetDescription()
    {
        return m_Description;
    }

    public void SetLineMode(LineMode newMode)
    {
        m_LineMode = newMode;
    }

    public LineMode GetLineMode()
    {
        return m_LineMode;
    }

    public void SetLinePriority(LinePriority newPrio)
    {
        m_LinePriority = newPrio;
    }

    public LinePriority GetLinePriority()
    {
        return m_LinePriority;
    }

    public bool GetHasRequired()
    {
        return m_RequiredNode != null;
    }
}
