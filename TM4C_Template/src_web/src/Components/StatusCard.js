import React from 'react';
import classes from './StatusCard.module.css';

const StatusCard = (props) => {
    return (
        <div className={classes.Wrapper}>
            <h3>{props.title}</h3>
            <p>{props.status}</p>
        </div>
    )
}

export default StatusCard;