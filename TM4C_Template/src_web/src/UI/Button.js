import React from 'react';
import classes from './Button.module.css';

const Button = props => {
  return (
      <a
        className={classes.Mybutton}
        onClick={props.onClick}
        style={{ backgroundColor: props.color }}
      >
        <span>{props.children}</span>
      </a>
  );
};

export default Button;
