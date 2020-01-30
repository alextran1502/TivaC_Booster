import React from 'react';
import classes from './Modal.module.css';
import Button from './Button';
const Modal = props => {
  return (
    <div class={classes.Modal} style={{ display: props.display }}>
      <div class={classes.modalContent}>
        <div class={classes.modalHeader}>
          <h4>{props.title}</h4>
        </div>
        <div class={classes.modalBody}>{props.children}</div>
        <div class={classes.modalBottom}>
          <Button onClick={props.onClose}>Close</Button>
        </div>
      </div>
    </div>
  );
};

export default Modal;
