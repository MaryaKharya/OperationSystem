#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack> 
#include <set>

using namespace std;


class RegularExpressions
{
public:
    RegularExpressions(istream& fileIn, ostream& fileOut)
        : m_fileIn(fileIn)
        , m_fileOut(fileOut)
    {
    }

    vector<char> getChars()
    {
        return m_chars;
    }

    vector<int> getStates()
    {
        return m_states;
    }

    void addStates()
    {
        m_states.push_back(m_number);
        m_number++;
    }

    void ReadRegularExpression()
    {
        char ch;
        while (m_fileIn >> ch)
        {
            if ((ch != '(') && (ch != ')') && (ch != '|') && (ch != '*') && (ch != '+'))
            {
                m_charsJump.push_back(ch);
            }
            m_chars.push_back(ch);
        }
    }

    void ReportIncorrectFormat()
    {
        m_fileOut << "ÕÂÍÓÂÍÚÌ˚È ÙÓÏ‡Ú ‰‡ÌÌ˚ı";
    }

    void InitialState(int state1, int state2, int number)
    {
        if (find(m_states.begin(), m_states.end(), state2) == m_states.end())
        {
            m_states.push_back(state2);
        }
        if (state1 >= m_table.size())
        {
            m_table.resize(state1 + 1);
        }
        m_table[state1].resize(m_charsJump.size());
        m_table[state1][number].insert(state2);
    }

    void Resize()
    {
        m_table.resize(temporaryEnd);
        m_table[temporaryEnd].resize(m_charsJump.size());
        m_table[temporaryEnd][m_number].insert(temporaryEnd);
    }

    void CreateInitialNonDeterministicTable()
    {
        m_isBracket = false;
        m_isOr = false;
        for (auto i = 0; i < m_chars.size(); i++)
        {
            switch (m_chars[i])
            {
            case '(':
            {
                auto s = m_states.size();
                if (!m_history.empty())
                {
                    if ((m_history.top().ch != '|') && (m_history.top().additional—h != '|'))
                    {
                        m_start = m_end;
                    }
                }
                std::cout << "(m_start - " << m_start << "(s - " << s << "\n";
                InitialState(m_start, s, 0);
                if (!m_history.empty())
                {
                    if ((m_history.top().additional—h == '|'))
                    {
                        m_history.push({ m_start, m_end, m_chars[i], '|',  m_history.top().additionalState });
                    }
                    else
                    {
                        m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                    }
                }
                else
                {
                    m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                }
                m_start = s;
                m_end = m_start;
                std::cout << "(m_start - " << m_start << "\n";
                m_history.push({ m_start, m_end, m_chars[i], 's',  m_start });
                //std::cout << " ( " << m_start << " ( " << m_end << " ( " << "\n";
                break;
            }
            case ')':
            {
                if (!m_history.empty())
                {
                    if (m_history.top().ch == ')')
                    {
                        while (m_history.top().ch != '(')
                        {
                            m_history.pop();
                        }
                        m_history.pop();
                        m_history.pop();
                    }
                    while (m_history.top().ch != '(')
                    {
                        m_history.pop();
                    }

                    History history = m_history.top();
                    //m_history.pop();
                    if (m_history.top().additional—h == '|')
                    {
                        //std::cout << ")m_end - " << m_end << " )m_start - " << m_start << "\n";
                        //InitialState(m_end, m_history.top().end, 0);
                        m_end = m_history.top().additionalState;
                    }
                    // m_history.push(history);
                }
                m_start = m_end;
                //std::cout << ")m_end - " << m_end << " )m_start - " << m_start << "\n";
                m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                //std::cout << " ) " << m_start << " ) " << m_end << " ) " << "\n";
                break;
            }
            case '|':
            {
                if (!m_history.empty())
                {
                    if ((m_history.top().ch == '*') || (m_history.top().ch == '+'))
                    {
                        m_end = m_history.top().end;
                        m_start = m_history.top().start;
                        //m_history.pop();
                    }
                    if (m_history.top().ch == ')')
                    {
                        m_end = m_history.top().end;
                        m_history.pop();
                        m_history.pop();
                        m_start = m_history.top().start;
                        m_history.pop();
                    }
                    else
                    {
                        m_end = m_history.top().end;
                        m_start = m_history.top().start;
                        //m_history.pop();
                    }
                }
                std::cout << "|m_end - " << m_end << "\n";
                m_history.push({ m_start, m_end, m_chars[i], m_chars[i], m_end });
                break;
            }
            case '*':
            {
                auto s = m_start;
                if (!m_history.empty())
                {
                    if (m_history.top().ch == ')')
                    {
                        m_history.pop();
                    }

                    if ((m_history.top().ch != '(') && (m_history.top().ch != '|') && (m_history.top().additional—h == '|'))
                    {
                        temporaryEnd = m_history.top().additionalState;
                    }
                    else
                    {
                        temporaryEnd = m_states.size();
                    }
                    // auto it = find(m_table[m_start][m_number].begin(), m_table[m_start][m_number].end(), m_end);
                     //auto number2 = std::distance(m_table[m_start][m_number].begin(), it);
                    if (m_history.top().additional—h == 's')
                    {
                        m_start = m_history.top().additionalState;
                        m_history.pop();
                    }
                    s = m_history.top().start;
                    std::cout << "*m_end - " << m_end << " *m_start - " << m_start << "\n";
                    InitialState(m_end, m_start, 0);
                    //m_table[m_start][m_number][number2] = m_end;
                    //m_start = m_end;
                    m_history.pop();
                }
                else
                {
                    temporaryEnd = m_states.size();
                }
                if (!m_history.empty())
                {
                    if (m_history.top().ch == '|')
                    {
                        m_end = m_history.top().end;
                        //std::cout << m_end;
                    }
                    else
                    {
                        m_end = temporaryEnd;
                    }
                    //m_end = m_states.size();
                }
                else
                {
                    m_end = temporaryEnd;
                }
                std::cout << "*m_start - " << m_start << " *m_end - " << m_end << "\n";
                InitialState(m_start, m_end, 0);

                m_start = s;
                if (i + 1 < m_chars.size())
                {
                    if (m_chars[i + 1] != '|')
                    {
                        m_start = m_end;
                    }
                }
                //std::cout << "*m_end - " << m_end << " *m_start - " << m_start << "\n";
                m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                //std::cout << " * " << m_start << " * " << m_end << " * " << "\n";
                break;
            }
            case '+':
            {
                /*if (m_history.top().ch == ')')
                {
                    m_history.pop();
                    m_start = m_history.top().start;
                    m_history.pop();
                    m_history.pop();
                }
                InitialState(m_end, m_start, 0);*/
                auto s = m_start;
                //std::cout << "+m_start - " << m_start << "\n";
                if (!m_history.empty())
                {
                    if (m_history.top().ch == ')')
                    {
                        m_history.pop();
                    }

                    if ((m_history.top().ch != '(') && (m_history.top().ch != '|') && (m_history.top().additional—h == '|'))
                    {
                        temporaryEnd = m_history.top().additionalState;
                    }
                    else
                    {
                        temporaryEnd = m_states.size();
                    }
                    if (m_history.top().additional—h == 's')
                    {
                        m_start = m_history.top().additionalState;
                        m_history.pop();
                    }
                    s = m_history.top().start;
                    std::cout << "+m_end - " << m_end << "+m_start - " << m_start << "\n";
                    InitialState(m_end, m_start, 0);
                    //m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                   // m_start = m_end;
                    m_history.pop();
                }
                else
                {
                    temporaryEnd = m_states.size();
                }

                m_start = m_end;

                if (!m_history.empty())
                {
                    if (m_history.top().ch == '|')
                    {
                        m_end = m_history.top().end;
                    }
                    else
                    {
                        m_end = temporaryEnd;
                    }
                }
                else
                {
                    m_end = temporaryEnd;
                }
                std::cout << "+m_start - " << m_start << " +m_end - " << m_end << "\n";
                InitialState(m_start, m_end, 0);

                m_start = s;
                if (i + 1 < m_chars.size())
                {
                    if (m_chars[i + 1] != '|')
                    {
                        m_start = m_end;
                    }
                }

                m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                //m_end = m_states.size();
                //InitialState(m_end, m_start, 0);
                //m_start = m_end;
                //std::cout << " + " << m_start << " + " << m_end << " + " << "\n";
                break;
            }
            default:
            {
                auto it = find(m_charsJump.begin(), m_charsJump.end(), m_chars[i]);
                m_number = std::distance(m_charsJump.begin(), it);
                auto s = m_states.size();
                if (!m_history.empty())
                {
                    if (m_history.top().ch == '|')
                    {
                        // m_start = m_history.top().start;
                        std::cout << "ch m_start - " << m_start << " ch s - " << s << "\n";
                        InitialState(m_start, s, 0);
                        if (i + 1 < m_chars.size())
                        {
                            if ((m_chars[i + 1] == '*') || (m_chars[i + 1] == '+'))
                            {
                                temporaryEnd = m_end;
                                m_end = m_states.size();
                            }
                        }
                        //m_end = m_history.top().end;
                    }
                    else if ((m_history.top().additional—h == '|'))
                    {
                        //m_start = m_history.top().start;
                        std::cout << "ch m_start - " << m_start << " ch s - " << s << "\n";
                        InitialState(m_start, s, 0);
                        m_end = m_states.size();
                    }
                    else
                    {
                        m_start = m_end;
                        std::cout << "ch m_start - " << m_start << " ch s - " << s << "\n";
                        InitialState(m_start, s, 0);
                        m_end = m_states.size();
                    }
                }
                else
                {
                    m_start = m_end;
                    std::cout << "ch m_start - " << m_start << " ch s - " << s << "\n";
                    InitialState(m_start, s, 0);
                    m_end = m_states.size();
                }
                std::cout << "ch s - " << s << " ch m_end - " << m_end << "\n";
                InitialState(s, m_end, m_number);

                if ((i + 1 < m_chars.size()) && (!m_history.empty()))
                {
                    if (((m_chars[i + 1] == '*') || (m_chars[i + 1] == '+')) && (m_history.top().ch == '|'))
                    {
                        m_history.push({ m_start, m_end, m_chars[i], '|', temporaryEnd });
                    }
                    else
                    {
                        m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                    }
                }
                else
                {
                    m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                }
                m_start = s;
                //std::cout << " CH " << m_start << " CH " << m_end << " CH " << m_history.top().ch2 << "\n";
                break;
            }
            }
        }
    }

    void GetTable()
    {
        for (auto i = 0; i < m_table.size(); i++)
        {
            for (auto j = 0; j < m_table[i].size(); j++)
            {
                for (const auto& z : m_table[i][j])
                {
                    std::cout << i << " " << j << " " << z << "\n";
                }
            }
        }
        std::cout << m_table.size();
    }


    void Add—losureInState()
    {
        for (auto i = 0; i < m_table.size(); i++)
        {
            m_states2.push_back({ i });
            std::cout << i << " ";
            if (m_table[i].size() != 0)
            {
                for (const auto& z : m_table[i][0])
                {
                    m_states2[i].insert(z);
                    std::cout << z << " ";
                }
                std::cout << "\n";
            }
        }
    }

    void CreateNewTableWithoutClosure()
    {
        m_table2.resize(m_states2.size());
        for (auto i = 0; i < m_table.size(); i++)
        {
            m_table2[i].resize(m_charsJump.size());
            for (auto j = 1; j < m_table[i].size(); j++)
            {
                for (const auto& z : m_table[i][j])
                {
                    m_table2[i][j].insert(z);
                    //std::cout << z << " ";
                }
            }
        }
    }

    void PrintDeterministicTableWithClosure(ostream& fileOut)
    {
        for (auto i = 0; i < m_table.size(); i++)
        {
            if (m_table[i].size() > 0)
            {
                for (const auto& j : m_states2[i])
                {
                    fileOut << j;
                }
                if (m_states2[i].size() > 0)
                {
                    fileOut << ": ";
                }
                for (auto j = 1; j < m_table[i].size(); j++)
                {
                    for (const auto& z : m_table[i][j])
                    {
                        fileOut << z << "";
                    }
                    fileOut << " ";
                }
                fileOut << "\n";
            }
        }
    }

    void AddRemainingClosures()
    {
        m_table3.resize(m_table.size());
        std::vector<std::vector<int>> statesElse(m_states2.size());
        for (auto i = 0; i < m_states2.size(); i++)
        {
            for (const auto& z : m_states2[i])
            {
                statesElse[i].push_back(z);
            }
        }
        for (auto i = 0; i < statesElse.size(); i++)
        {
            m_table3[i].resize(m_table[i].size());
            for (auto z = 0; z < statesElse[i].size(); z++)
            {
                //std::cout << z << "||||";
                if ((statesElse[i][z] != i) && (statesElse[i][z] < m_table.size()) && (m_table[statesElse[i][z]].size() > 0))
                {
                    for (const auto& j : m_table[statesElse[i][z]][0])
                    {
                        m_states2[i].insert(j);
                        if (find(statesElse[i].begin(), statesElse[i].end(), j) == statesElse[i].end())
                        {
                            statesElse[i].push_back(j);
                        }
                    }
                }
            }

        }
        DetermineAutomaton();
    }

    void DetermineAutomaton()
    {
        std::vector<std::vector<std::set<int>>> table;
        std::vector<int> finalStates();
        int count = 1;
        std::vector<std::vector<int>> finalTable(m_table.size());
        m_states3.push_back(m_states2[0]);
        table.push_back(m_table[0]);
        for (auto l = 0; l < m_states3.size(); l++)
        {
            //m_states3.resize(l + 1);
            table.resize(l + 1);
            if (m_states3.size() > l)
            {
                for (const auto& i : m_states3[l])
                {
                    //std::cout << "///" << i << "\n";
                    if (m_table.size() > i)
                    {
                        for (auto j = 1; j < m_table[i].size(); j++)
                        {
                            table[l].resize(m_table[i].size());
                            for (const auto& z : m_table[i][j])
                            {
                                for (const auto& k : m_states2[z])
                                {
                                    table[l][j].insert(k);
                                }
                                //std::cout << "\n";
                            }
                        }
                    }
                }
                for (auto j = 1; j < table[l].size(); j++)
                {
                    if (find(m_states3.begin(), m_states3.end(), table[l][j]) == m_states3.end())
                    {
                        m_states3.push_back(table[l][j]);
                    }
                }
            }

        }
        m_table = table;
        m_states2 = m_states3;
        ReplaceAutomatonWithNewStates();
    }

    void ReplaceAutomatonWithNewStates()
    {
        std::vector<int> finalStates(m_states2.size());
        std::vector<std::vector<int>> finalTable(m_table.size());
        int count = 0;

        for (auto i = 0; i < m_states2.size(); i++)
        {
            if ((m_states2[i].size() > 0))
            {
                finalStates[i] = count;
                count++;
            }
        }

        for (auto i = 0; i < m_table.size(); i++)
        {
            finalTable[i].resize(m_table[i].size());
            if ((m_table[i].size() > 0) && (m_states2[i].size() > 0))
            {
                for (auto z = 1; z < m_table[i].size(); z++)
                {
                    if (m_table[i][z].size() > 0)
                    {
                        auto stateFind = find(m_states2.begin(), m_states2.end(), m_table[i][z]);
                        auto numFind = std::distance(m_states2.begin(), stateFind);
                        if (stateFind != m_states2.end())
                        {
                            finalTable[i][z] = finalStates[numFind];
                        }
                    }
                }
            }
        }

        for (auto i = 0; i < finalTable.size(); i++)
        {
            if ((m_table[i].size() > 0))
            {
                std::cout << "s" << finalStates[i] << ": ";
                for (auto z = 0; z < finalTable[i].size(); z++)
                {
                    if (finalTable[i][z] != 0)
                    {
                        std::cout << "s" << finalTable[i][z] << " ";
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }
                std::cout << "\n";
            }
        }
    }


private:
    vector<char> m_chars;
    vector<char> m_charsJump = { 'e' };
    vector<int> m_states = { 0 };
    struct History
    {
        int start = 0;
        int end = 0;
        char ch;
        char additional—h;
        int additionalState = -1;
    };
    stack<History> m_history;
    std::vector<std::vector<std::set<int>>> m_table;
    std::vector<std::vector<std::set<int>>> m_table2;
    std::vector<std::vector<std::set<int>>> m_table3;
    std::vector<std::set<int>> m_states2;
    std::vector<std::set<int>> m_states3;
    istream& m_fileIn;
    ostream& m_fileOut;
    int m_number = 2;
    bool m_isOr = false;
    bool m_isBracket = false;
    bool m_isAsterisk = false;
    bool m_isPlus = false;
    int temporaryEnd = 0;
    int temporaryEnd = 0;
    int m_start = 0;
    int m_end = 0;

};


