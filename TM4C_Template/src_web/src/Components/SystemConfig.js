import React from 'react';
import classes from './SystemConfig.module.css';
import Modal from '../UI/Modal';
import Button from '../UI/Button';

class SystemConfig extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      eepromData: [],
      eepromIndex: 0,
      modalDisplayProps: 'none'
    };

    this.getEEPROM = this.getEEPROM.bind(this);
    this.massEraseEEPROM = this.massEraseEEPROM.bind(this);
    this.handleChange = this.handleChange.bind(this);
    this.closeModalHandler = this.closeModalHandler.bind(this);
    this.openModalHandler = this.openModalHandler.bind(this);
  }

  openModalHandler = () => {
    console.log(this.state);
    this.state.modalDisplayProps === 'none'
      ? this.setState({
          modalDisplayProps: 'block'
        })
      : this.setState({
          modalDisplayProps: 'none'
        });
  };

  closeModalHandler = () => {
    console.log('close close');
    this.setState({
      modalDisplayProps: 'none'
    });
  };

  getEEPROM() {
    fetch('/getROM')
      .then(response => {
        return response.json();
      })
      .then(result => {
        console.log(result)
        this.setState({
          eepromData: result
        });
      })
      .catch(err => console.log(err));
  }

  massEraseEEPROM() {
    fetch('/massEraseROM')
    .then(response => {
      return response.json();
    })
    .then(result => {
      console.log(result)
      this.setState({
        eepromData: result
      });
    })
    .catch(err => console.log(err));
  }

  handleChange(event) {
    this.setState({ eepromIndex: event.target.value });
  }

  render() {
    return (
      <div className={classes.Wrapper}>
        <h1 style={{ fontSize: '50px' }}>System Configuration</h1>
        <label>
          Name:
          <input
            type='text'
            value={this.state.eepromIndex}
            onChange={this.handleChange}
          />
        </label>

        <Button onClick={this.getEEPROM}>Read EEPROM</Button>
        <Button onClick={this.massEraseEEPROM}>Erase EEPROM</Button>

        <Button onClick={this.openModalHandler}>SHOW CONFIG</Button>
        {this.state.eepromData.MyKey}
        <Modal
          display={this.state.modalDisplayProps}
          onClose={this.closeModalHandler}
          title='EEPROM'
        >
          {this.state}
        </Modal>

        <p className={classes.footer}>
          Conductix-Wampfler © {new Date().getFullYear()}
        </p>
      </div>
    );
  }
}

export default SystemConfig;
