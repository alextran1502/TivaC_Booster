import React from 'react';
import classes from './SystemStatus.module.css'
import StatusCard from './StatusCard';


class SystemStatus extends React.Component {
    render() {
        return (
            <div className={classes.Wrapper}>
                <img src="https://www.conductix.us/sites/all/themes/cxw_us/logo.png" alt="Conductix Logo"/>
                <h1 style={{fontSize: '50px'}}>System Status</h1>
                <div className={classes.StatusCardWrapper}>
                    <StatusCard title="Input Card Version" status="16-Input"/>
                    <StatusCard title="Output Card Version" status="16-Output"/>
                    <StatusCard title="Operating Mode" status="1 Master - 2 Slave"/>
                    <StatusCard title="Current Role" status="Master"/>
                    <StatusCard title="Pin Mapping" status="Default"/>
                    <StatusCard title="Bluetooth" status="Enable"/>
                    <StatusCard title="Data Logging" status="Disable"/>
                </div>
            </div>
        )
    }
}

export default SystemStatus;