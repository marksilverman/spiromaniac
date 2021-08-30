## Spiromaniac
This code generates animated patterns based on spirograph mechanics. It uses three virtual wheels nested inside one another.
# Math
To plot a regular circle, loop over the angles between 0 and 2 * pi. cosine gives you your x coordinate and sine give you y. Multiply by your radius and you have a circle.
```javascript
    x = radius1 * cos(angle1);
    y = radius1 * sin(angle1);
```
Here's how to plot a circle rolling inside another circle (for regular spirograph-type patterns). See [wikipedia](https://en.wikipedia.org/wiki/Spirograph#Mathematical_basis) if you want to know why this works. _offset_ is where you would stick your pen in the spirograph wheel.
```javascript
    // 1st wheel
    x = (radius1 - radius2) * cos(angle1);
    y = (radius1 - radius2) * sin(angle1);

    // 2nd wheel
    angle2 = angle1 * (radius1 - radius2) / radius2;
    x += offset * cos(angle2);
    y -= offset * sin(angle2);
```
Finally, here's how to plot a circle rolling inside a circle rolling inside a circle! I'm pretty sure the math is right; pls get in touch if it can be improved.
```javascript
    // 1st wheel
    x = (radius1 - radius2 + radius3) * cos(angle1);
    y = (radius1 - radius2 + radius3) * sin(angle1);

    // 2nd wheel
    angle2 = angle1 * (radius1 - radius2) / radius2;
    x += cos(angle2);
    y -= sin(angle2);

    // 3rd wheel
    angle3 = angle2 * (radius1 - radius2 + radius3) / radius3;
    x += offset * cos(angle3);
    y -= offset * sin(angle3);
```
