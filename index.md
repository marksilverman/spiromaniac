## Spiromaniac

This code generates patterns based on spirograph mechanics. It uses three virtual wheels nested inside one another. For a given angle *angle1*, here's how we plot a point:

```javascript
    // 1st wheel
    x = (radius1 - radius2 + radius3) * cos(angle1);
    y = (radius1 - radius2 + radius3) * sin(angle1);

    // 2nd wheel
    angle2 = angle1 * (radius1 - radius2) / radius2;
    x += (radius3 - radius2) * Math.cos(angle2);
    y -= (radius3 - radius2) * Math.sin(angle2);

    // 3rd wheel
    angle3 = angle2 * (radius1 - radius2 + radius3) / radius3;
    x += offset * radius3 * Math.cos(angle3);
    y -= offset * radius3 * Math.sin(angle3);
```
