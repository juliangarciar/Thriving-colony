 // complex number rotation along azimuthal angle theta ===================
        tempAngle = deltaX*rotSpeed;
        cosA = cos(tempAngle);
        sinA = sin(tempAngle);

        camTar2 = camTar1 - camPos;

        camTar1.x = cosA*camTar2.x - sinA*camTar2.z;
        camTar1.y = camTar2.y;
        camTar1.z = cosA*camTar2.z + sinA*camTar2.x;

        direction.x = camTar1.x;
        direction.y = camTar1.z;
        direction.normalize();

        // quaternion rotation along polar angle phi =============================

        tempAngle = deltaY*rotSpeed / 2;
        currentAngle = acos(camTar1.y / camTar1.getLength());

        if (currentAngle > 2.84f)
            tempAngle = tempAngle > 0 ? tempAngle : 0;
        else if (currentAngle < 0.3f)
            tempAngle = tempAngle < 0 ? tempAngle : 0;

        cosA = cos(tempAngle);
        sinA = sin(tempAngle);

        aSinA = -sinA*direction.y;
        bSinA = sinA*direction.x;

        cosASq = cosA*cosA;
        aSinASq = aSinA*aSinA;
        bSinASq = bSinA*bSinA;

        bSinATarTemp2X = bSinA*camTar1.x;
        cosATarTemp2Y = cosA*camTar1.y;
        aSinATarTemp2Z = aSinA*camTar1.z;

        camTar2.x = camTar1.x*(cosASq + aSinASq - bSinASq) + 2.0f * bSinA*(aSinATarTemp2Z - cosATarTemp2Y);
        camTar2.y = camTar1.y*(cosASq - aSinASq - bSinASq) + 2.0f * cosA*(bSinATarTemp2X - aSinATarTemp2Z);
        camTar2.z = camTar1.z*(cosASq - aSinASq + bSinASq) + 2.0f * aSinA*(bSinATarTemp2X + cosATarTemp2Y);

        tarHeight = camTar2.y + camHeight;

        std::cout << camTar1.x << " " << camTar1.y << " " << camTar1.z << "\n";
        camTar1 = camTar2 + camPos;
        std::cout << camTar1.x << " " << camTar1.y << " " << camTar1.z << "\n";