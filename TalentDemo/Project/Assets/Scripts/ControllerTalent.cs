using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ControllerTalent : MonoBehaviour
{
    //Public vars
    public bool m_IsDragMode = false;
    public TalentNode[] m_TalentNodes;

    //Public static vars
    public static int m_TalentPoints = 20;
    public static int m_SpentPoints = 0;
    public static float m_CanvasScaleFactor;

    //Component vars
    Canvas m_Canvas;
    Image m_Outline;
    Text m_CurrentText;
    Text m_HeaderText;
    Text m_InstructionText;
    TalentNode m_CurrentlySelectedNode;

    void Start()
    {
        m_Canvas = GetComponent<Canvas>();
        m_CanvasScaleFactor = m_Canvas.scaleFactor;
        m_CurrentText = GameObject.Find("CurrentText").GetComponent<Text>();
        m_HeaderText = GameObject.Find("HeaderText").GetComponent<Text>();
        m_InstructionText = GameObject.Find("InstructionText").GetComponent<Text>();
        m_Outline = GameObject.Find("Outline").GetComponent<Image>();
        m_Outline.gameObject.SetActive(false);

        //Find all talent nodes
        var nodes = GameObject.FindGameObjectsWithTag("TalentNode");
        if (nodes.Length > 0)
        {
            m_TalentNodes = new TalentNode[nodes.Length];
            for (int i = 0; i < nodes.Length; i++)
            {
                m_TalentNodes[i] = nodes[i].GetComponent<TalentNode>();
            }
        }
        else
            Debug.Log("Couldn't find any talent nodes!");

        if (m_InstructionText)
            m_InstructionText.text = "Click on any node to select it, if its requirement is met then a point is spent on that node." + "\n" +
                "\nRight click on any node that is not leading to anything to remove a point." + "\n" +
                "\nThe colors on the lines between nodes change depending on state:" +
                "\nRed: The required node has no points." +
                "\nYellow: The required node has points." +
                "\nGreen: The required node and the node it is leading to has points." + "\n" +
                "\nPress 1 or 2 to change current node's line mode." + "\n" +
                "\nPress Q or W to change current node's line priority if current line mode is two-step." + "\n" +
                "\nPress F1 to toggle drag-mode, when active you can move the nodes around with the mouse.";
    }

    void Update()
    {
        CurrentlySelectedUpdate();

        TextUpdate();

        if (Input.GetKeyDown(KeyCode.F1))
            m_IsDragMode = !m_IsDragMode;

        if (Input.GetKeyDown(KeyCode.Escape))
            Application.Quit();
    }

    void CurrentlySelectedUpdate()
    {
        for (int i = 0; i < m_TalentNodes.Length; i++)
        {
            if (m_TalentNodes[i].GetIsHover() && Input.GetMouseButtonDown(0))
                SetCurrentlySelected(m_TalentNodes[i]);
            if (m_TalentNodes[i].GetIsHover() && Input.GetMouseButton(0) && m_IsDragMode)
            {
                m_TalentNodes[i].transform.position = Input.mousePosition;
                break;
            }
        }

        //Displays currently selected node
        if (m_CurrentText && m_CurrentlySelectedNode)
        {
            if (!m_Outline.gameObject.activeSelf)
                m_Outline.gameObject.SetActive(true);

            m_Outline.transform.position = m_CurrentlySelectedNode.transform.position;

            string lineMode;
            string linePrio;
            if (m_CurrentlySelectedNode.GetHasRequired())
            {
                lineMode = "Current line mode: " + m_CurrentlySelectedNode.GetLineMode().ToString();
                linePrio = "Current line priority: " + m_CurrentlySelectedNode.GetLinePriority().ToString();
            }
            else
            {
                lineMode = "Current node has no required node.";
                linePrio = "";
            }

            m_CurrentText.text = "Currently selected node: " + m_CurrentlySelectedNode.GetTitle() + "\n" + lineMode + "\n" + linePrio;

            if (m_CurrentlySelectedNode.GetHasRequired())
            {
                //Change lineprio and linemode depending on input for selected node
                if (Input.GetKeyDown(KeyCode.Q))
                    m_CurrentlySelectedNode.SetLinePriority(LinePriority.X);
                else if (Input.GetKeyDown(KeyCode.W))
                    m_CurrentlySelectedNode.SetLinePriority(LinePriority.Y);

                if (Input.GetKeyDown(KeyCode.Alpha1))
                    m_CurrentlySelectedNode.SetLineMode(LineMode.Direct);
                else if (Input.GetKeyDown(KeyCode.Alpha2))
                    m_CurrentlySelectedNode.SetLineMode(LineMode.Two_Step);
            }
        }
        else if (m_CurrentText && !m_CurrentlySelectedNode)
        {
            if (m_Outline.gameObject.activeSelf)
                m_Outline.gameObject.SetActive(false);
            m_CurrentText.text = "No currently selected node";
        }
    }

    void TextUpdate()
    {
        if (m_HeaderText)
            m_HeaderText.text = "Talent Tree Demo:\nNumber of points to spend: " + m_TalentPoints + "\nNumber of spent points: " + m_SpentPoints + "\nDrag mode: " + m_IsDragMode;
    }

    void SetCurrentlySelected(TalentNode newNode)
    {
        m_CurrentlySelectedNode = newNode;
    }

    public static bool GetHasPoints()
    {
        return m_TalentPoints > 0;
    }
    public static void AddPoints(int num)
    {
        m_TalentPoints += num;
        m_SpentPoints -= num;
    }
}
