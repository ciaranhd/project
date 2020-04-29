# Gross pay computtion#







hrs = input("Enter Hours: ")
hrs = float(hrs)
pay_rate_normal = input("Enter normal rate of pay: ")
pay_rate_normal = float(pay_rate_normal)


def gross_pay(aa):
    if hrs < 40:
        added = (pay_rate_normal * hrs)
        return added
    else:
        added = ((pay_rate_normal * 40) + ((hrs - 40) * (pay_rate_normal * 1.5)))
        return added

x = gross_pay('aa')
print(x)
