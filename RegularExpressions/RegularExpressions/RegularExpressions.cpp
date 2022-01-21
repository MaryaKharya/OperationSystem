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

    vector<size_t> getStates()
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
                if (find(m_charsJump.begin(), m_charsJump.end(), ch) == m_charsJump.end())
                {
                    m_charsJump.push_back(ch);
                }
            }
            m_chars.push_back(ch);
        }
    }

    void InitialState(size_t start, size_t end, size_t number)
    {
        if (find(m_states.begin(), m_states.end(), end) == m_states.end())
        {
            m_states.push_back(end);
        }
        if (start >= m_table.size())
        {
            m_table.resize(start + 1);
        }
        m_table[start].resize(m_charsJump.size());
        m_table[start][number].insert(end);
    }

    void CreateInitialNonDeterministicTable()
    {
        for (size_t i = 0; i < m_chars.size(); i++)
        {
            switch (m_chars[i])
            {
            case '(':
            {
                size_t temporaryStart = m_states.size();
                if (!m_history.empty())
                {
                    if ((m_history.top().ch != '|') && (m_history.top().additionalСh != '|'))
                    {
                        m_start = m_end;
                    }
                }
                InitialState(m_start, temporaryStart, 0);
                if (!m_history.empty())
                {
                    if ((m_history.top().additionalСh == '|'))
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
                m_start = temporaryStart;
                m_end = m_start;
                m_history.push({ m_start, m_end, m_chars[i], 's',  m_start });
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

                    if (m_history.top().additionalСh == '|')
                    {
                        m_end = m_history.top().additionalState;
                    }
                }
                m_start = m_end;
                m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
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
                    }
                }
                m_history.push({ m_start, m_end, m_chars[i], m_chars[i], m_end });
                break;
            }
            case '*':
            {
                size_t temporaryStart = m_start;
                size_t temporaryEnd;
                if (!m_history.empty())
                {
                    if (m_history.top().ch == ')')
                    {
                        m_history.pop();
                    }

                    if ((m_history.top().ch != '(') && (m_history.top().ch != '|') && (m_history.top().additionalСh == '|'))
                    {
                        temporaryEnd = m_history.top().additionalState;
                    }
                    else
                    {
                        temporaryEnd = m_states.size();
                    }
                    if (m_history.top().additionalСh == 's')
                    {
                        m_start = m_history.top().additionalState;
                        m_history.pop();
                    }
                    temporaryStart = m_history.top().start;
                    InitialState(m_end, m_start, 0);
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
                InitialState(m_start, m_end, 0);

                m_start = temporaryStart;
                if (i + 1 < m_chars.size())
                {
                    if (m_chars[i + 1] != '|')
                    {
                        m_start = m_end;
                    }
                }
                m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                break;
            }
            case '+':
            {
                size_t temporaryStart = m_start;
                size_t temporaryEnd;
                if (!m_history.empty())
                {
                    if (m_history.top().ch == ')')
                    {
                        m_history.pop();
                    }

                    if ((m_history.top().ch != '(') && (m_history.top().ch != '|') && (m_history.top().additionalСh == '|'))
                    {
                        temporaryEnd = m_history.top().additionalState;
                    }
                    else
                    {
                        temporaryEnd = m_states.size();
                    }
                    if (m_history.top().additionalСh == 's')
                    {
                        m_start = m_history.top().additionalState;
                        m_history.pop();
                    }
                    temporaryStart = m_history.top().start;
                    InitialState(m_end, m_start, 0);
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
                InitialState(m_start, m_end, 0);

                m_start = temporaryStart;
                if (i + 1 < m_chars.size())
                {
                    if (m_chars[i + 1] != '|')
                    {
                        m_start = m_end;
                    }
                }

                m_history.push({ m_start, m_end, m_chars[i], m_chars[i] });
                break;
            }
            default:
            {
                auto it = find(m_charsJump.begin(), m_charsJump.end(), m_chars[i]);
                m_number = std::distance(m_charsJump.begin(), it);
                size_t temporaryStart = m_states.size();
                size_t temporaryEnd;
                if (!m_history.empty())
                {
                    if (m_history.top().ch == '|')
                    {
                        InitialState(m_start, temporaryStart, 0);
                        if (i + 1 < m_chars.size())
                        {
                            if ((m_chars[i + 1] == '*') || (m_chars[i + 1] == '+'))
                            {
                                temporaryEnd = m_end;
                                m_end = m_states.size();
                            }
                        }
                    }
                    else if ((m_history.top().additionalСh == '|'))
                    {
                        InitialState(m_start, temporaryStart, 0);
                        m_end = m_states.size();
                    }
                    else
                    {
                        m_start = m_end;
                        InitialState(m_start, temporaryStart, 0);
                        m_end = m_states.size();
                    }
                }
                else
                {
                    m_start = m_end;
                    InitialState(m_start, temporaryStart, 0);
                    m_end = m_states.size();
                }
                InitialState(temporaryStart, m_end, m_number);

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
                m_start = temporaryStart;
                break;
            }
            }
        }
    }
        
    void GetTable()
    {
        for (size_t i = 0; i < m_table.size(); i++)
        {
            for (size_t j = 0; j < m_table[i].size(); j++)
            {
                for (const auto& z : m_table[i][j])
                {
                   m_fileOut << i << " " << m_charsJump[j] << " " << z << "\n";
                }
            }
        }
        m_fileOut << "\n";
    }


    void AddСlosureInState()
    {
        for (size_t i = 0; i < m_table.size(); i++)
        {
            m_states2.push_back({ i });
            if (m_table[i].size() != 0)
            {
                for (const auto& z : m_table[i][0])
                {
                    m_states2[i].insert(z);
                }
            }
        }
    }

    void CreateNewTableWithoutClosure()
    {
        m_table2.resize(m_states2.size());
        for (size_t i = 0; i < m_table.size(); i++)
        {
            m_table2[i].resize(m_charsJump.size());
            for (size_t j = 1; j < m_table[i].size(); j++)
            {
                m_table2[i].push_back(m_table[i][j]);
            }
        }
    }

    void Prsize_tDeterministicTableWithClosure(ostream& fileOut)
    {
        for (size_t i = 0; i < m_table.size(); i++)
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
                for (size_t j = 1; j < m_table[i].size(); j++)
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
        std::vector<std::vector<size_t>> statesElse(m_states2.size());
        for (size_t i = 0; i < m_states2.size(); i++)
        {
            for (const auto& z : m_states2[i])
            {
                statesElse[i].push_back(z);
            }
        }
        for (size_t i = 0; i < statesElse.size(); i++)
        {
            for (size_t z = 0; z < statesElse[i].size(); z++)
            {
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
        std::vector<std::vector<std::set<size_t>>> table;
        size_t count = 1;
        m_states3.push_back(m_states2[0]);
        table.push_back(m_table[0]);
        for (size_t l = 0; l < m_states3.size(); l++)
        {
            table.resize(l + 1);
            if (m_states3.size() > l)
            {
                for (const auto& i : m_states3[l])
                {
                    if (m_table.size() > i)
                    {
                        for (size_t j = 1; j < m_table[i].size(); j++)
                        {
                            table[l].resize(m_table[i].size());
                            for (const auto& z : m_table[i][j])
                            {
                                if (m_table.size() <= z)
                                {
                                    table[l][j].insert(z);
                                    continue;
                                }
                                for (const auto& k : m_states2[z])
                                {
                                    table[l][j].insert(k);
                                }
                            }
                        }
                    }
                }
                for (size_t j = 1; j < table[l].size(); j++)
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
        std::vector<size_t> finalStates(m_states2.size());
        std::vector<std::vector<size_t>> finalTable(m_table.size());
        size_t count = 0;

        for (size_t i = 0; i < m_states2.size(); i++)
        {
            if ((m_states2[i].size() > 0))
            {
                finalStates[i] = count;
                count++;
            }
        }

        for (size_t i = 0; i < m_table.size(); i++)
        {
            finalTable[i].resize(m_table[i].size());
            if ((m_table[i].size() > 0) && (m_states2[i].size() > 0))
            {
                for (size_t z = 1; z < m_table[i].size(); z++)
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

        for (size_t i = 1; i < m_charsJump.size(); i++)
        {
            m_fileOut << m_charsJump[i] << " ";
        }
        m_fileOut << "\n";
        for (size_t i = 0; i < finalTable.size(); i++)
        {
            if ((m_table[i].size() > 0))
            {
                m_fileOut << "s" << finalStates[i] << ": ";
                for (size_t z = 0; z < finalTable[i].size(); z++)
                {
                    if (finalTable[i][z] != 0)
                    {
                        m_fileOut << "s" << finalTable[i][z] << " ";
                    }
                    else
                    {
                        m_fileOut << " ";
                    }
                }
                m_fileOut << "\n";
            }
        }
    }


private:
    vector<char> m_chars;
    vector<char> m_charsJump = { 'e' };
    vector<size_t> m_states = { 0 };
    struct History
    {
        size_t start = 0;
        size_t end = 0;
        char ch;
        char additionalСh;
        size_t additionalState = 0;
    };
    stack<History> m_history;
    std::vector<std::vector<std::set<size_t>>> m_table;
    std::vector<std::vector<std::set<size_t>>> m_table2;
    std::vector<std::set<size_t>> m_states2;
    std::vector<std::set<size_t>> m_states3;
    istream& m_fileIn;
    ostream& m_fileOut;
    size_t m_number = 2;
    size_t m_start = 0;
    size_t m_end = 0;

};

size_t main()
{
    ifstream fileIn("Input.txt");
    ofstream fileOut("Output.txt");
    RegularExpressions expression(fileIn, fileOut);
    expression.ReadRegularExpression();
    auto chars = expression.getChars();
    auto states = expression.getStates();
    expression.CreateInitialNonDeterministicTable();
    expression.GetTable();
    expression.AddСlosureInState();
    expression.CreateNewTableWithoutClosure();
    expression.AddRemainingClosures();
    //expression.Prsize_tDeterministicTableWithClosure(fileOut);
    for (size_t i = 0; i < chars.size(); i++)
    {
        std::cout << chars[i] << " ";
    }
    std::cout << "\n";
    for (size_t i = 0; i < states.size(); i++)
    {
    }
    std::cout << "\n";
}
