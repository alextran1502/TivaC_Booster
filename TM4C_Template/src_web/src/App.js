import React from 'react';
import './App.css';
import SystemStatus from './Components/SystemStatus';
import SystemConfig from './Components/SystemConfig';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {  };
  }

  render() {
    return (
      <div className='App-Wrapper'>
        <div className='system-status'>
          <SystemStatus />
        </div>
        <div className='system-config'>
          <SystemConfig />
        </div>
      </div>
    );
  }
}

export default App;
