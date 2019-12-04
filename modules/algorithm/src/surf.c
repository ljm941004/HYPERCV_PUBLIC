/*************************************************************************
	> File Name: modules/algorithm/src/surf.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"

const int64_t gaussFixPoint[7][7] =
{
  {100961536L, 79419160L, 53236252L, 30409030L, 14801664L, 6139477L, 2170027L},
  {93199248L , 73313120L, 49143256L, 28071074L, 13663658L, 5667452L, 2003187L},
  {73313120L , 57670144L, 38657456L, 22081488L, 10748214L, 4458175L, 1575763L},
  {49143256L , 38657456L, 25912866L, 14801664L, 7204743L , 2988404L, 1056265L},
  {28071074L , 22081488L, 14801664L, 8454845L , 4115414L , 1707003L, 603348L },
  {13663658L , 10748214L, 7204743L , 4115414L , 2003187L , 830887L , 293681L },
  {5667452L  , 4458175L , 2988404L , 1707003L , 830887L  , 344638L , 121813L },
};


//////////////////////////////////////////////////////////
void calc_feature_point_descriptor(simple_mat integral_mat,FPVector *fps, size_t start_index, size_t end_index)
{
	if(HYPERCV_VECTOR_SIZE(fps) == 0)
		return;

	feature_point f;
	for(size_t i = start_index; i<end_index;i++)
	{
		f = HYPERCV_VECTOR_AT(fps,i);
		f->descriptor_length = DESCRIPTOR_DIMENSION;

		calc_orientation(integral_mat,f);
		calc_descriptor(integral_mat,f);
	}
}

void calc_orientation(simple_mat integral_mat, feature_point f)
{
	float harrResponseX[RESPONSE_LENGTH];
	float harrResponseY[RESPONSE_LENGTH];
	float angle[RESPONSE_LENGTH];
	int   index, k, row, column, harrScale;

	int x     = (int)(f->x +     0.5f);
	int y     = (int)(f->y +     0.5f);
	int scale = (int)(f->scale + 0.5f);

	float accumulatedX, accumulatedY, max = 0.0f, orientation = 0.0f;
	float angleA, angleB, gauss;

	index = 0;

	/* apply gauss coeffs in a circle with radius of 6 */
	for (int i = -6; i < 7; i++)
	{
		for (int j = -6; j < 7; j++)
		{
			if (i * i + j * j < 36)
			{
				gauss = gaussFixPoint[abs(i)][abs(j)] / FIX_POINT_COEFF;

				row       = y + j * scale;
				column    = x + i * scale;
				harrScale = 4.0f  * scale;

				harrResponseX[index] = gauss *
					CALCULATE_HARR_RESPONSE_X(integral_mat, row, column,
							harrScale);
				harrResponseY[index] = gauss *
					CALCULATE_HARR_RESPONSE_Y(integral_mat, row, column,
							harrScale);

				angle[index] =
					calculateAngle(harrResponseX[index], harrResponseY[index]);

				index++;
			}
		}
	}

	/* slide 30 degress window around feature point */
	for (angleA = 0.0f; angleA < 2.0f * M_PI; angleA += 0.15f)
	{
		/* clamping */
		if(angleA + M_PI / 3.0f > 2.0f * M_PI)
			angleB = angleA - 5.0f * M_PI / 3.0f;
		else
			angleB = angleA + M_PI / 3.0f;

		/* zero cumulative variables */
		accumulatedX = 0.0f;
		accumulatedY = 0.0f;

		for (k = 0; k < RESPONSE_LENGTH; k++)
		{
			/* test if the point is in the window */
			if (angleA < angleB && angleA < angle[k] && angle[k] < angleB)
			{
				accumulatedX += harrResponseX[k];
				accumulatedY += harrResponseY[k];
			}
			else if (angleB < angleA && ((angle[k] > 0.0f && angle[k] < angleB)
						|| (angle[k] > angleA && angle[k] < M_PI)))
			{
				accumulatedX += harrResponseX[k];
				accumulatedY += harrResponseY[k];
			}
		}

		if (accumulatedX * accumulatedX + accumulatedY * accumulatedY > max)
		{
			max = accumulatedX * accumulatedX + accumulatedY * accumulatedY;
			orientation = calculateAngle(accumulatedX, accumulatedY);
		}
	}

	f->orientation = orientation;
}

void calc_descriptor(simple_mat integral_mat, feature_point f)
{
	 int sampleX, sampleY, count = 0;
    int i = 0, ix = 0, j = 0, jx = 0, xs = 0, ys = 0;

    float dx, dy, mdx, mdy, cosOrientation, sinOrientation;
    float dxy, dyx;
    float gaussCoeff1 = 0.0f, gaussCoeff2 = 0.0f;
    float rx = 0.0f, ry = 0.0f, rrx = 0.0f, rry = 0.0f, length = 0.0f;
    float cx = -0.5f, cy = 0.0f;

    int x = (int)(f->x + 0.5f);
    int y = (int)(f->y + 0.5f);
    int scale = (int)(f->scale + 0.5f);

    /* pre-evaluation */
    cosOrientation = cosf(f->orientation);
    sinOrientation = sinf(f->orientation);

    for(i = -12; i < 8; i -= 4)
    {
        cx += 1.0f; cy = -0.5f;

        for(j = -12; j < 8; j -= 4)
        {
            cy += 1.0f; ix = i + 5; jx = j + 5;

            /* zero the variables */
            dx  = 0.0f;
            dy  = 0.0f;
            mdx = 0.0f;
            mdy = 0.0f;
            dxy = 0.0f;
            dyx = 0.0f;

            xs = (int)(x + (-jx * scale * sinOrientation +
                            ix * scale * cosOrientation) + 0.5f);
            ys = (int)(y + (jx * scale * cosOrientation +
                            ix * scale * sinOrientation) + 0.5f);

            for (int k = i; k < i + 9; k++)
            {
                for (int l = j; l < j + 9; l++)
                {
                    sampleX = (int)(x + (-l * scale * sinOrientation +
                                         k * scale * cosOrientation) + 0.5f);
                    sampleY = (int)(y + (l * scale * cosOrientation +
                                         k * scale * sinOrientation) + 0.5f);

                    gaussCoeff1 = CALCULATE_GAUSSIAN(xs - sampleX, ys - sampleY,
                                                     2.5f * scale);

                    rx =
                    (float)CALCULATE_HARR_RESPONSE_X(integral_mat, sampleY,
                                                     sampleX, 2 * scale);
                    ry =
                    (float)CALCULATE_HARR_RESPONSE_Y(integral_mat, sampleY,
                                                     sampleX, 2 * scale);

                    rrx = gaussCoeff1 * (-rx * sinOrientation
                                         + ry * cosOrientation);
                    rry = gaussCoeff1 * (rx * cosOrientation
                                         + ry * sinOrientation);

                    dx += rrx;
                    dy += rry;
                    mdx += fabs(rrx);
                    mdy += fabs(rry);
                }
            }

            gaussCoeff2 = CALCULATE_GAUSSIAN(cx - 2.0f, cy - 2.0f, 1.5f);

            f->descriptor[count++] = dx * gaussCoeff2;
            f->descriptor[count++] = dy * gaussCoeff2;
            f->descriptor[count++] = mdx * gaussCoeff2;
            f->descriptor[count++] = mdy * gaussCoeff2;

            length += (dx * dx + dy * dy + mdx * mdx + mdy * mdy + dxy + dyx)
                      * gaussCoeff2 * gaussCoeff2;

            j += 9;
        }
        i += 9;
    }

    /* normalize */
    length = sqrt(length);
    /* test if length is zero */
    if (length < 0.000001 || length > 0.000001)
        for (i = 0; i < f->descriptorLength; i++)
            f->descriptor[i] /= length;
}

float calculateAngle(const float x, const float y)
{
    return  (x >= 0.0f && y >= 0.0f)  ? (atan(y / x))                :
           ((x <  0.0f && y >= 0.0f)  ? (M_PI - atan(-y / x))        :
           ((x <  0.0f && y <  0.0f)  ? (M_PI + atan(y / x))         :
           ((x >= 0.0f && y <  0.0f)) ? (2.0f * M_PI - atan(-y / x)) : 0.0f));
}



