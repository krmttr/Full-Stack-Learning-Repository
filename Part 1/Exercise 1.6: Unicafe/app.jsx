import { useState } from 'react'

const Header = (props) => {

  console.log(props)
  return <h1>{props.getFeedback}</h1>
}

const Statistics = ({ good, neutral, bad }) => {
  const all = good + neutral + bad;
  const average = (good - bad) / all;
  const positive = (good / all) * 100;

  if (all === 0) {
    return <p>No feedback given</p>;
  }

  return (
    <div>
      <table>
       <tr>
        <td>good</td>
        <td>{good}</td>
      </tr>
      <tr>
        <td>neutral</td>
        <td>{neutral}</td>
      </tr>
      <tr>
        <td>bad</td>
        <td>{bad}</td>
      </tr>
      <tr>
        <td>all</td>
        <td>{all}</td>
      </tr>
      <tr>
        <td>average</td>
        <td>{(good-bad)/all}</td>
      </tr>
      <tr>
        <td>positive</td>
        <td>{(good/all)*100} %</td>
      </tr>
      </table>
    </div>
  );
};

const Button = ({ text, onClick }) => {
  return <button onClick={onClick}>{text}</button>;
};

/*
const StatisticLine = ({ text, value }) => {
  return (
    <div>
      <p>
        {text} {value}
      </p>
    </div>
  );
};
*/

const App = () => {
  const [good, setGood] = useState(0)
  const [neutral, setNeutral] = useState(0)
  const [bad, setBad] = useState(0)

  const handleGoodClick = () => {
    setGood(good + 1);
  };

  const handleNeutralClick = () => {
    setNeutral(neutral + 1);
  };

  const handleBadClick = () => {
    setBad(bad + 1);
  };

  const getFeedback = {
    name: 'get feeedback',
    parts: [
      {
        name: 'good',
        num_of_clicks_good: good,
      },
      {
        name: 'neutral',
        num_of_clicks_neutral: neutral,
      },
      {
        name: 'bad',
        num_of_clicks_bad: bad,
      },
    ],
  };

  return (
  <div>
    <h1>give feedback</h1>
    <div>
      <Button text="good" onClick={handleGoodClick} />
      <Button text="neutral" onClick={handleNeutralClick} />
      <Button text="bad" onClick={handleBadClick} />
      </div>
      <h1>statistics</h1>
      <Statistics good={good} neutral={neutral} bad={bad} />
      </div>
  )
}

export default App
